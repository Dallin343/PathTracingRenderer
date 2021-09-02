cmake_minimum_required(VERSION 3.20)
project(CS655)

set(CMAKE_CXX_STANDARD 17)


include_directories(${CMAKE_SOURCE_DIR} Vendor/glm/glm Vendor/antlr/runtime)

add_subdirectory(Vendor/glm)

add_executable(CS655 main.cpp Renderable/Material.cpp Rays/Ray.cpp Renderable/Sphere.cpp Rays/Hit.cpp Rays/Hit.h Scene/SceneDescription.cpp Scene/SceneDescription.h Scene/Camera.cpp Scene/Camera.h Lights/Light.cpp Lights/Light.h Lights/DirectionalLight.cpp Lights/DirectionalLight.h Parser/MySDFListener.cpp Parser/MySDFListener.h)


target_link_libraries(CS655 PRIVATE glm::glm ${CMAKE_SOURCE_DIR}/Vendor/antlr/lib/libantlr4-runtime.a)
