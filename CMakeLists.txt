cmake_minimum_required(VERSION 3.17)
project(OpenGLEngine)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
set(GCC_COVERAGE_LINK_FLAGS "-lgcov")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(SFML COMPONENTS system window network graphics audio REQUIRED)

add_executable(OpenGLEngineTests tests/tests.cpp)
add_executable(OpenGLEngine main.cpp external/stb/stb_image.cpp utils/shaderLoader.cpp)

include_directories(${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS} ${SFML_DIR})

set(LIBRARIES
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        sfml-system
        sfml-window
        sfml-network
        sfml-graphics
        sfml-audio
        )

target_link_libraries(OpenGLEngineTests ${LIBRARIES})
target_link_libraries(OpenGLEngine ${LIBRARIES})