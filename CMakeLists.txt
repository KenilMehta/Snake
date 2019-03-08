cmake_minimum_required(VERSION 3.12)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project("Snake")
set(ProjectPath "/home/kmehta/repo/Snake")
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(COMPILER_FLAGS "-march=native")
set(COMPILER_WARRNINGS "-Wall -Werror -Wextra")

set(CMAKE_CXX_FLAGS "${COMPILER_FLAGS} ${COMPILER_WARRNINGS}")

set(SFML_INCLUDE_DIR "/home/kmehta/repo/Snake/SFML-2.5.1/include")
set(SFML_LIB_DIR "/home/kmehta/repo/Snake/SFML-2.5.1/lib")
link_directories(${SFML_LIB_DIR})

set(GENERATED_OUTPUT_PATH "GeneratedFiles")
set(sbe_SCHEMA "/home/kmehta/repo/Snake/schema.xml")
set(sbe_HEADERS "${GENERATED_OUTPUT_PATH}/NewPlayer.h")
set(SBE_JAR "${ProjectPath}/sbe-all.jar")
set(Java_JAVA_EXECUTABLE "/usr/bin/java")
add_custom_command(
        OUTPUT ${sbe_HEADERS}
        DEPENDS "${sbe_SCHEMA}"
        COMMAND "${Java_JAVA_EXECUTABLE}" "-Dsbe.output.dir=${ProjectPath}/${GENERATED_OUTPUT_PATH}" -Dsbe.target.language=CPP -jar "${SBE_JAR}" "${sbe_SCHEMA}"
        COMMENT "Generating SBE sources"
)

add_library(UdpSocket UdpSocket.cpp)
add_library(Epoll EpollWrapper.cpp)
add_custom_target(sbe_generation DEPENDS ${sbe_HEADERS})


add_executable(Server main.cpp Snake.cpp constants.h Server.cpp SbeEncoderDecoder.cpp)
target_include_directories(Server PRIVATE ${SFML_INCLUDE_DIR})
target_link_libraries(Server sfml-system sfml-window sfml-graphics UdpSocket Epoll)

add_executable(Client Client.cpp UdpSocket.cpp Snake.cpp EpollWrapper.cpp SbeEncoderDecoder.cpp)
target_include_directories(Client PRIVATE ${SFML_INCLUDE_DIR})
target_link_libraries(Client sfml-system sfml-window sfml-graphics UdpSocket Epoll)


add_dependencies(Server sbe_generation)
add_dependencies(Client sbe_generation)
message(STATUS "=== ${PROJECT_NAME} ===")
message(STATUS "C++ Version         : ${CMAKE_CXX_STANDARD}")
message(STATUS "C++ Compilar Flags  : ${CMAKE_CXX_FLAGS}")
message(STATUS "CMake build type    : ${CMAKE_BUILD_TYPE}")
message(STATUS "SFML include DIR    : ${SFML_INCLUDE_DIR}")
message(STATUS "SFML lib DIR        : ${SFML_LIB_DIR}")
message(STATUS "=== >>>><<<< ===")