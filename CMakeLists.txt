cmake_minimum_required(VERSION 3.16)

project(LearnOpenGL)
set(${project_name} LearnOpenGL)
set(CMAKE_CXX_STANDARD 17)
set(INCLUDES includes/Window.h includes/MyGraphics.h)
set(SRC src/Window.cpp src/MyGraphics.cpp)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

set(LIBS glfw OpenGL glew)


add_executable(LearnOpenGL main.cpp ${SRC} ${INCLUDES})
target_link_libraries(LearnOpenGL ${LIBS})