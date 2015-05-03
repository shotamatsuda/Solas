#!/bin/sh
#
#  build.sh
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

readonly IOS_BUILD_DIR="$(pwd)/ios/build"
readonly OSX_BUILD_DIR="$(pwd)/osx/build"

readonly DEPOT_TOOLS_REPO="https://chromium.googlesource.com/chromium/tools/depot_tools.git"
readonly SKIA_REPO="https://skia.googlesource.com/skia.git"

download_depot_tools() {
  git clone "${DEPOT_TOOLS_REPO}"
}

download_skia() {
  export PATH="$(pwd)/depot_tools":"${PATH}"
  gclient config --name . --unmanaged "${SKIA_REPO}"
  gclient sync
  git checkout master
}

build_skia() {
  export GYP_GENERATORS="ninja,xcode"
  SKIA_GYP_OUTPUT_DIR="osx" "./gyp_skia"
  ninja -C "out/osx/Debug" dm
  ninja -C "out/osx/Release" dm

  export GYP_DEFINES="skia_os='ios' skia_arch_type='arm' armv7='1' arm_neon='0'"
  SKIA_GYP_OUTPUT_DIR="iphoneos" "./gyp_skia"
  ninja -C "out/iphoneos/Debug" dm
  ninja -C "out/iphoneos/Release" dm

  export GYP_DEFINES="skia_os='ios' skia_arch_type='x86'"
  SKIA_GYP_OUTPUT_DIR="iphonesim" "./gyp_skia"
  ninja -C "out/iphonesim/Debug" dm
  ninja -C "out/iphonesim/Release" dm
}

merge_libraries() {
}

# download_depot_tools
mkdir -p "skia"
pushd "skia"
  # download_skia
  # build_skia
popd
