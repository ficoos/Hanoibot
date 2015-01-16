cmake_minimum_required (VERSION 2.8)
project (GC2)

add_subdirectory(libs/glfw)
include_directories(libs/glfw/include)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
add_definitions("-std=c++11")

add_executable(GC2 src/main.cxx)
target_link_libraries(GC2 glfw ${GLFW_LIBRARIES})


