cmake_minimum_required(VERSION 2.8)
include(../CMakeCommon.txt)

project(csim6502_tests CXX)
include(GoogleTest)

enable_testing()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fprofile-instr-generate -fcoverage-mapping -Werror -pedantic -Wall -Wextra")
include_directories(${GTEST_INCLUDE_DIRS})
#find_package(GTest REQUIRED)

set(TEST_FILES HeapRAMTest BitsetTest UtilTest CPUTest)

foreach(testFile ${TEST_FILES})
    add_executable(${testFile} ${testFile}.cc)
    target_link_libraries(${testFile} gtest gtest_main csim6502_base)
    add_test(${testFile} ${testFile})
endforeach()

