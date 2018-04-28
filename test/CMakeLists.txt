cmake_minimum_required(VERSION 2.8)
include(../CMakeCommon.txt)

project(csim6502_tests CXX)
include(GoogleTest)

enable_testing()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fprofile-instr-generate -fcoverage-mapping -Werror -pedantic -Wall -Wextra")
include_directories(${GTEST_INCLUDE_DIRS})
#find_package(GTest REQUIRED)

set(BASE_TEST_FILES HeapRAMTest UtilTest CPUTest MockRAMTest)

foreach(testFile ${BASE_TEST_FILES})
    add_executable(${testFile} ${testFile}.cc)
    target_link_libraries(${testFile} gtest gtest_main csim6502_base)
    add_test(${testFile} ${testFile})
endforeach()

set(OPCODE_TEST_FILES)

foreach(testFile ${OPCODE_TEST_FILES})
    add_executable(${testFile} ${testFile}.cc)
    target_link_libraries(${testFile} gtest gtest_main csim6502_opcode)
    add_test(${testFile} ${testFile})
endforeach()
