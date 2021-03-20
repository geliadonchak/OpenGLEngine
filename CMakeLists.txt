cmake_minimum_required(VERSION 3.17)
project(OpenGLEngine)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(SFML COMPONENTS system window network graphics audio REQUIRED)

add_executable(OpenGLEngine main.cpp Vector.hpp Matrix.hpp)

include_directories(${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS} ${SFML_DIR})

target_link_libraries(OpenGLEngine
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        sfml-system
        sfml-window
        sfml-network
        sfml-graphics
        sfml-audio
        )
