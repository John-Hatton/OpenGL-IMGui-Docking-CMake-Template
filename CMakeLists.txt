cmake_minimum_required(VERSION 3.0.0)
project(OpenGL-IMGui-Docking-CMake-Template VERSION 0.0.1)


set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DFLAC__NO_DLL")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DFLAC__NO_DLL")


# Makes it so a command line doesn't start up with the program too (for windows only)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mwindows")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}  /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules)
find_path(OpenCV_DIR "OpenCVConfig.cmake" C:/dev/sdk/opencv/build_mingw/install DOC "Root directory of OpenCV")
link_directories(libs/glfw)

include_directories(libs/glad)
include_directories(libs/KHR)
include_directories(libs/imgui)
include_directories(libs/implot)
include_directories(libs/glfw)
include_directories(include)



#target_link_options(OpenGL-IMGui-Docking-CMake-Template -mwindows)
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
add_executable(OpenGL-IMGui-Docking-CMake-Template ${SOURCES})


find_package(OpenGL REQUIRED)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# add libs you need
set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs)

target_link_libraries(OpenGL-IMGui-Docking-CMake-Template PRIVATE ${OPENGL_gl_LIBRARY})
target_link_libraries(OpenGL-IMGui-Docking-CMake-Template PRIVATE glfw3)
target_link_libraries(OpenGL-IMGui-Docking-CMake-Template PRIVATE ${OpenCV_LIBS} "-static")
file(COPY resources DESTINATION /)



