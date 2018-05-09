cmake_minimum_required(VERSION 2.8)
include(../CMakeCommon.txt)
include(GoogleTest)

enable_testing()
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(../)
find_package(GTest REQUIRED)

file(GLOB BASE_TEST_FILES *Test.cc)
add_executable(BaseTest ${BASE_TEST_FILES})
target_link_libraries(BaseTest gtest gtest_main gmock csim6502_base pthread)
add_test(BaseTest BaseTest)

file(GLOB OPCODE_TEST_FILES opcode/*Test.cc)
add_executable(OpcodeTest ${OPCODE_TEST_FILES} opcode/MockAddressingMode.cc)
target_link_libraries(OpcodeTest gtest gtest_main gmock csim6502_base csim6502_opcode pthread)
add_test(OpcodeTest OpcodeTest)
