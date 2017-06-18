cmake_minimum_required (VERSION 2.8)
project (GC2)

add_subdirectory(libs/glfw)
include_directories(libs/glfw/include)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
link_directories(${OPENGL_LIBRARY_DIRS})
add_definitions(${OPENGL_DEFINITIONS})
if(NOT OPENGL_GLU_FOUND)
	message(ERROR " GLU not found!")
endif(NOT OPENGL_GLU_FOUND)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
add_definitions("-std=c++11 -DGLFW_INCLUDE_GLU")

add_executable(GC2
	src/main.cxx
	src/Torus.cpp
	src/Pole.cpp
	src/Ring.cxx
	src/Arm.cpp
	src/HanoiState.cxx
)
target_link_libraries(GC2 glfw ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES})


