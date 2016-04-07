#!/bin/sh
#
#  build_boost.sh
#
#  The MIT License
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

readonly BOOST_VERSION="1.58.0"
readonly BOOST_MODULES=""
readonly BOOST_NO_BUILD=true
readonly COMPILER="clang"
readonly COMPILER_FLAGS="-std=c++11 -stdlib=libc++"
readonly IOS_SDK_VERSION=$(xcodebuild -showsdks | grep iphoneos |
    egrep "\d+\.\d+" -o | tail -1)
readonly OSX_SDK_VERSION=$(xcodebuild -showsdks | grep osx |
    egrep "\d+\.\d+" -o | tail -1)

readonly PROJECT_DIR="$(cd "$(dirname "$0")/../"; pwd)"
readonly BUILD_DIR="${PROJECT_DIR}/build/boost"
readonly DEVELOPER_DIR=$("xcode-select" -print-path)
readonly IOS_SDK_ROOT="${DEVELOPER_DIR}/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS${IOS_SDK_VERSION}.sdk"
readonly SIM_SDK_ROOT="${DEVELOPER_DIR}/Platforms/iPhoneSimulator.platform/Developer/SDKs/iPhoneSimulator${IOS_SDK_VERSION}.sdk"
readonly OSX_SDK_ROOT="${DEVELOPER_DIR}/Platforms/MacOSX.platform/Developer/SDKs/MacOSX${OSX_SDK_VERSION}.sdk"
readonly OSX_BUILD_DIR="${BUILD_DIR}/osx"
readonly IOS_BUILD_DIR="${BUILD_DIR}/ios"
readonly BOOST_ARCHIVE="${BUILD_DIR}/${BOOST_VERSION}.tar.bz2"
readonly BOOST_DIR="${BUILD_DIR}/${BOOST_VERSION}"

readonly ARM_XCRUN="xcrun --sdk iphoneos"
readonly SIM_XCRUN="xcrun --sdk iphonesimulator"
readonly OSX_XCRUN="xcrun --sdk macosx"

cleanup() {
  echo "Cleaning everything before we start to build..."
  rm -rf "${BOOST_DIR}/iphoneos-build"
  rm -rf "${BOOST_DIR}/iphonesimulator-build"
  rm -rf "${BOOST_DIR}/osx-build"
  rm -rf "${BUILD_DIR}/include"
  rm -rf "${BUILD_DIR}/lib"
  rm -rf "${IOS_BUILD_DIR}"
  rm -rf "${OSX_BUILD_DIR}"
}

download_boost() {
  if [[ ! -d "${BUILD_DIR}" ]]; then
    mkdir -p "${BUILD_DIR}"
  fi
  if [[ ! -s "${BOOST_ARCHIVE}" ]]; then
    echo "Downloading boost ${BOOST_VERSION}"
    local version=$(echo "${BOOST_VERSION}" | sed "s/\./_/g")
    curl -L --retry 10 -o "${BOOST_ARCHIVE}" \
        "http://sourceforge.net/projects/boost/files/boost/${BOOST_VERSION}/boost_${version}.tar.bz2/download"
  fi
}

extract_boost() {
  if [[ ! -f "${BOOST_ARCHIVE}" ]]; then
    echo "Source archive is missing."
    exit
  fi
  echo "Extracting boost into ${BOOST_DIR}..."
  if [[ ! -d "${BOOST_DIR}" ]]; then
    mkdir -p "${BOOST_DIR}"
    tar -xjf "${BOOST_ARCHIVE}" -C "${BOOST_DIR}" --strip-components=1
  fi
  if [[ -d "${BOOST_DIR}" ]]; then
    echo "Unpacked as ${BOOST_DIR}"
  fi
}

bootstrap_boost() {
  cd "${BOOST_DIR}"
  if [[ ! "${BOOST_MODULES}" ]]; then
    echo "Bootstrapping"
    ./bootstrap.sh
  else
    local libraries=$(echo "${BOOST_MODULES}" |
        sed -E "s/^ +//g" | sed -E "s/ +/,/g")
    echo "Bootstrapping (with libraries ${libraries})"
    ./bootstrap.sh --with-libraries="${libraries}"
  fi
}

compile_boost() {
  cd "${BOOST_DIR}"
  if [[ ! BOOST_NO_BUILD ]]; then
    ./b2 \
        -j8 \
        -d0 \
        --build-dir="iphoneos-build" \
        --stagedir="iphoneos-build/stage" \
        --prefix="${BUILD_DIR}" \
        toolset="${COMPILER}" \
        cflags="-arch armv7 -arch armv7s -arch arm64 -fvisibility=hidden \
            -fvisibility-inlines-hidden ${COMPILER_FLAGS}" \
        architecture="arm" \
        target-os="iphone" \
        threading="multi" \
        define="_LITTLE_ENDIAN" \
        link="static" \
        include="${IOS_SDK_ROOT}/usr/include" \
        stage
    ./b2 \
        -j8 \
        -d0 \
        --build-dir="iphonesimulator-build" \
        --stagedir="iphonesimulator-build/stage" \
        toolset="${COMPILER}" \
        cflags="-arch i386 -arch x86_64 -fvisibility=hidden \
            -fvisibility-inlines-hidden ${COMPILER_FLAGS}" \
        architecture="x86" \
        target-os="iphone" \
        threading="multi" \
        link="static" \
        include="${SIM_SDK_ROOT}/usr/include" \
        stage
  fi
  # Install for extracting headers
  ./b2 \
      -j8 \
      -d0 \
      --build-dir="iphoneos-build" \
      --stagedir="iphoneos-build/stage" \
      --prefix="${BUILD_DIR}" \
      toolset="${COMPILER}" \
      cflags="-arch armv7 -arch armv7s -arch arm64 -fvisibility=hidden \
          -fvisibility-inlines-hidden ${COMPILER_FLAGS}" \
      architecture="arm" \
      target-os="iphone" \
      threading="multi" \
      define="_LITTLE_ENDIAN" \
      link="static" \
      include="${IOS_SDK_ROOT}/usr/include" \
      install
  rm -r "${BUILD_DIR}/lib"
}

create_universal_libraries() {
  cd "${BOOST_DIR}"
  mkdir -p "${BUILD_DIR}/lib"
  echo "Creating universal libraries..."
  for name in ${BOOST_MODULES}; do
    ${ARM_XCRUN} lipo -create \
        "iphoneos-build/stage/lib/libboost_${name}.a" \
        "iphonesimulator-build/stage/lib/libboost_${name}.a" \
        -o "${BUILD_DIR}/lib/libboost_${name}.a"
  done
}

cleanup
download_boost
extract_boost
bootstrap_boost
compile_boost
create_universal_libraries
