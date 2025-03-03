cmake_minimum_required(VERSION 3.20)
project(the_zero_overhead_principle)

file(GLOB CPP_FILES ${CMAKE_SOURCE_DIR}/C++/*.cpp)
file(GLOB C_FILES ${CMAKE_SOURCE_DIR}/C/*.c)

add_executable(cpp_program ${CPP_FILES})
target_compile_features(cpp_program PRIVATE cxx_std_20)

add_executable(c_program ${C_FILES})
target_compile_features(c_program PRIVATE c_std_17)

# Generate assembly code for both targets C and C++ to see the compiled code.
add_custom_command(TARGET cpp_program PRE_BUILD
        COMMAND ${CMAKE_CXX_COMPILER} -S ${CPP_FILES} -o ${CMAKE_SOURCE_DIR}/C++/program.asm --std=c++23 -Os -Wall -Wextra -Wpedantic
        COMMENT "Generating assembly for C++ program"
)
add_custom_command(TARGET c_program PRE_BUILD
        COMMAND ${CMAKE_C_COMPILER} -S ${C_FILES} -o ${CMAKE_SOURCE_DIR}/C/program.asm --std=c23 -Os -Wall -Wextra -Wpedantic
        COMMENT "Generating assembly for C program"
)
message(STATUS "C++ Flags: ${CMAKE_CXX_FLAGS}")
message(STATUS "C Flags: ${CMAKE_C_FLAGS}")

add_custom_target(${PROJECT_NAME} DEPENDS cpp_program c_program)