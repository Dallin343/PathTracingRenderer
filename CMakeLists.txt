cmake_minimum_required(VERSION 3.20)
project(CS655)

set(CMAKE_CXX_STANDARD 17)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(Vendor/glfw)

include_directories(Vendor/glm/glm Vendor/glfw/include Vendor/glad/include)

add_subdirectory(Vendor/glm)

add_library(GLAD STATIC Vendor/glad/src/glad.c Vendor/glad/include/glad/glad.h)
add_executable(CS655 main.cpp)

find_package(OpenGL REQUIRED)

target_link_libraries(CS655 PRIVATE glfw OpenGL::GL GLAD glm::glm)
