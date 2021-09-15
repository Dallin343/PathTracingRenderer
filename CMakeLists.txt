cmake_minimum_required(VERSION 3.20)
project(CS655)

set(CMAKE_CXX_STANDARD 17)

LIST(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(ANTLR4_ZIP_REPOSITORY ${PROJECT_SOURCE_DIR}/Vendor/antlr/antlr4-4.9.2.zip)
# add external build for antlrcpp
include(ExternalAntlr4Cpp)
# add antrl4cpp artifacts to project environment
include_directories(${ANTLR4_INCLUDE_DIRS})

set(ANTLR_EXECUTABLE ${PROJECT_SOURCE_DIR}/Vendor/antlr/antlr-4.9.2-complete.jar)
find_package(ANTLR REQUIRED)
# Call macro to add lexer and grammar to your build dependencies.
antlr_target(SDFParser
        ${CMAKE_CURRENT_SOURCE_DIR}/SDF.g4
        PACKAGE antlrcpp
        VISITOR)

include_directories(${ANTLR_SDFParser_OUTPUT_DIR})
include_directories(${CMAKE_SOURCE_DIR} Vendor/glm/glm)

add_subdirectory(Vendor/glm)

add_executable(CS655
        ${ANTLR_SDFParser_CXX_OUTPUTS}
        main.cpp
        Renderable/Material.cpp
        Rays/Ray.cpp
        Renderable/Sphere.cpp
        Rays/Hit.cpp
        Rays/Hit.h
        Scene/SceneDescription.cpp
        Scene/SceneDescription.h
        Scene/Camera.cpp
        Scene/Camera.h
        Lights/Light.cpp
        Lights/Light.h
        Lights/DirectionalLight.cpp
        Lights/DirectionalLight.h
        Parser/MySDFVisitor.cpp
        Parser/MySDFVisitor.h Parser/MySDFParser.cpp Parser/MySDFParser.h Renderer.cpp Renderer.h Renderable/Polygon.cpp Renderable/Polygon.h Renderable/Triangle.cpp Renderable/Triangle.h Lights/PointLight.cpp Lights/PointLight.h)


target_link_libraries(CS655 PRIVATE glm::glm antlr4_shared)
