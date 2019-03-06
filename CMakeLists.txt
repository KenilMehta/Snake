cmake_minimum_required(VERSION 3.12)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project("Snake")

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(COMPILER_FLAGS "-march=native")
set(COMPILER_WARRNINGS "-Wall -Werror -Wextra")

set(CMAKE_CXX_FLAGS "${COMPILER_FLAGS} ${COMPILER_WARRNINGS}")

set(SFML_INCLUDE_DIR "/home/kmehta/repo/Snake/SFML-2.5.1/include")
set(SFML_LIB_DIR "/home/kmehta/repo/Snake/SFML-2.5.1/lib")
link_directories(${SFML_LIB_DIR})

add_executable(Snake main.cpp Snake.cpp constants.h)
target_include_directories(Snake PRIVATE ${SFML_INCLUDE_DIR})
target_link_libraries(Snake sfml-system sfml-window sfml-graphics)

message(STATUS "=== ${PROJECT_NAME} ===")
message(STATUS "C++ Version         : ${CMAKE_CXX_STANDARD}")
message(STATUS "C++ Compilar Flags  : ${CMAKE_CXX_FLAGS}")
message(STATUS "CMake build type    : ${CMAKE_BUILD_TYPE}")
message(STATUS "SFML include DIR    : ${SFML_INCLUDE_DIR}")
message(STATUS "SFML lib DIR        : ${SFML_LIB_DIR}")
message(STATUS "=== >>>><<<< ===")