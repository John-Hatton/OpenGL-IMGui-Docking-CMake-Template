cmake_minimum_required(VERSION 3.0.0)
project(OpenGL-IMGui-Docking-CMake-Template VERSION 0.0.1)
# Makes it so a command line doesn't start up with the program too (for windows only)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mwindows")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}  /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")


link_directories(libs/glfw)

include_directories(libs/glad)
include_directories(libs/KHR)
include_directories(libs/imgui)
include_directories(libs/implot)
include_directories(libs/glfw)
include_directories(include)


file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
add_executable(OpenGL-IMGui-Docking-CMake-Template ${SOURCES})

#target_link_options(OpenGL-IMGui-Docking-CMake-Template -mwindows)

find_package(OpenGL REQUIRED)
target_link_libraries(OpenGL-IMGui-Docking-CMake-Template PRIVATE ${OPENGL_gl_LIBRARY})
target_link_libraries(OpenGL-IMGui-Docking-CMake-Template PRIVATE glfw3)
file(COPY resources DESTINATION /)
