cmake_minimum_required(VERSION 3.1.0)

project(qtqrencode)

option(WITH_TESTS "Enable building of the tester app" OFF)

find_path(QRENCODE_INCLUDE_DIR qrencode.h)
find_library(QRENCODE_LIBRARY qrencode)

find_package(Qt5Core 5.0 REQUIRED)
find_package(Qt5Gui 5.0 REQUIRED)
find_package(Qt5Svg 5.0 REQUIRED)
find_package(Qt5Test 5.0 REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 11)

include_directories(SYSTEM ${QRENCODE_INCLUDE_DIR})
add_subdirectory(src)

if(WITH_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif(WITH_TESTS)
