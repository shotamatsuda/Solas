#!/bin/sh
#
#  skia.sh
#
#  MIT License
#
#  Copyright (C) 2015 Shota Matsuda
#
#  Permission is hereby granted, free of charge, to any person obtaining a
#  copy of this software and associated documentation files (the "Software"),
#  to deal in the Software without restriction, including without limitation
#  the rights to use, copy, modify, merge, publish, distribute, sublicense,
#  and/or sell copies of the Software, and to permit persons to whom the
#  Software is furnished to do so, subject to the following conditions:
#
#  The above copyright notice and this permission notice shall be included in
#  all copies or substantial portions of the Software.
#
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
#  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
#  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
#  DEALINGS IN THE SOFTWARE.
#

readonly DEPOT_TOOLS_GIT="https://chromium.googlesource.com/chromium/tools/depot_tools.git"
readonly SKIA_GIT="https://skia.googlesource.com/skia.git"

readonly PROJECT_DIR="$(cd "$(dirname "$0")/../"; pwd)"
readonly BUILD_DIR="${PROJECT_DIR}/build"
readonly DEPOT_TOOLS_DIR="${BUILD_DIR}/depot_tools"
readonly SKIA_DIR="${BUILD_DIR}/skia"

download_depot_tools() {
  git clone "${DEPOT_TOOLS_GIT}" "${DEPOT_TOOLS_DIR}"
}

download_skia() {
  export PATH="${DEPOT_TOOLS_DIR}":"${PATH}"
  mkdir -p "${SKIA_DIR}/skia"
  pushd "${SKIA_DIR}/skia"
    gclient config --name . --unmanaged "${SKIA_GIT}"
    gclient sync
    git checkout master
  popd
}

build_skia() {
  pushd "${SKIA_DIR}/skia"
    export GYP_GENERATORS="ninja,xcode"

    echo "Building for OS X"
    "./gyp_skia"
    ninja -C "out/Release" skia_lib tools

    echo "Building for iOS"
    GYP_DEFINES="skia_os='ios' skia_arch_type='arm' armv7='1' arm_neon='0'" "./gyp_skia"
    ninja -C "out/Release-iphoneos" skia_lib tools

    echo "Building for iOS Simulator"
    GYP_DEFINES="skia_os='ios' skia_arch_type='x86_64'" "./gyp_skia"
    # Because gyp_skia doesn't generate ninja files for iPhone Simulator, we
    # need to replace the occurrences of the target architecture and the SDK
    # directory by hand.
    find "out/Release-iphonesimulator" -type f -name "*.ninja" -exec \
        sed -i -e 's/armv7/x86_64/g' {} \;
    find "out/Release-iphonesimulator" -type f -name "*.ninja" -exec \
        sed -i -e 's|iPhoneOS.platform/Developer/SDKs/iPhoneOS|iPhoneSimulator.platform/Developer/SDKs/iPhoneSimulator|g' {} \;
    ninja -C "out/Release-iphonesimulator" skia_lib tools
  popd
}

copy_libraries_in_place() {
  echo "Copying libraries in place"
  mkdir -p "${SKIA_DIR}/osx/x86_64"
  mkdir -p "${SKIA_DIR}/ios/armv7"
  mkdir -p "${SKIA_DIR}/ios/x86_64"
  for file in $(find "${SKIA_DIR}/skia/out/Release" -name "*.a"); do
    cp -n "${file}" "${SKIA_DIR}/osx/x86_64"
  done
  for file in $(find "${SKIA_DIR}/skia/out/Release-iphoneos" -name "*.a"); do
    cp -n "${file}" "${SKIA_DIR}/ios/armv7"
  done
  for file in $(find "${SKIA_DIR}/skia/out/Release-iphonesimulator" -name "*.a"); do
    cp -n "${file}" "${SKIA_DIR}/ios/x86_64"
  done
}

create_universal_files() {
  echo "Decomposing libraries to object files"
  mkdir -p "${SKIA_DIR}/osx/x86_64/obj"
  mkdir -p "${SKIA_DIR}/ios/armv7/obj"
  mkdir -p "${SKIA_DIR}/ios/x86_64/obj"
  for file in $(find "${SKIA_DIR}/osx/x86_64" -name "*.a"); do
    cd "${SKIA_DIR}/osx/x86_64/obj"; ar -x "${file}"
  done
  for file in $(find "${SKIA_DIR}/ios/armv7" -name "*.a"); do
    cd "${SKIA_DIR}/ios/armv7/obj"; ar -x "${file}"
  done
  for file in $(find "${SKIA_DIR}/ios/x86_64" -name "*.a"); do
    cd "${SKIA_DIR}/ios/x86_64/obj"; ar -x "${file}"
  done

  echo "Linking everything within architectures"
  rm "${SKIA_DIR}"/osx/*/libskia.a
  rm "${SKIA_DIR}"/ios/*/libskia.a
  pushd "${SKIA_DIR}/osx/x86_64"
    xcrun ar crus "libskia.a" obj/*.o
  popd
  pushd "${SKIA_DIR}/ios/armv7"
    xcrun ar crus "libskia.a" obj/*.o
  popd
  pushd "${SKIA_DIR}/ios/x86_64"
    xcrun ar crus "libskia.a" obj/*.o
  popd

  echo "Creating universal files"
  rm "${SKIA_DIR}"/osx/libskia.a
  rm "${SKIA_DIR}"/ios/libskia.a
  xcrun lipo -create "${SKIA_DIR}"/osx/*/libskia.a -o "${SKIA_DIR}/osx/libskia.a"
  xcrun lipo -create "${SKIA_DIR}"/ios/*/libskia.a -o "${SKIA_DIR}/ios/libskia.a"
}

download_depot_tools
download_skia
build_skia
copy_libraries_in_place
create_universal_files
