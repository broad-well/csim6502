cmake_minimum_required(VERSION 2.8)
include(../CMakeCommon.txt)
include(GoogleTest)

enable_testing()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(../)
#find_package(GTest REQUIRED)

set(BASE_TEST_FILES HeapRAMTest UtilTest CPUTest MockRAMTest RAMTest)

foreach(testFile ${BASE_TEST_FILES})
    add_executable(${testFile} ${testFile}.cc)
    target_link_libraries(${testFile} gtest gtest_main gmock csim6502_base pthread)
    add_test(${testFile} ${testFile})
endforeach()

set(OPCODE_TEST_FILES AddressingModeTest SystemTest StackTest StorageTest JumpTest ArithmeticTest)

foreach(testFile ${OPCODE_TEST_FILES})
    add_executable(${testFile} opcode/${testFile}.cc)
    target_link_libraries(${testFile} gtest gtest_main gmock csim6502_base csim6502_opcode)
    add_test(${testFile} ${testFile})
endforeach()
