//
// Created by Dallin Hagman on 9/7/21.
//

#ifndef CS655_RENDERER_H
#define CS655_RENDERER_H

#include "Scene/SceneDescription.h"
#include <array>

const uint8_t MAX_DEPTH = 3;

class Renderer {
private:
    std::optional<std::unique_ptr<Rays::Hit>> _findHit(Rays::Ray *ray);
    glm::dvec3 _traceRay(Rays::Ray* ray, uint8_t depth);
    glm::dvec3 _calculateIllumination(Rays::Ray* ray, Rays::Hit* hit);

    static std::unique_ptr<Rays::ReflectionRay> _reflect(Rays::Ray* ray, Rays::Hit* hit);
    static std::unique_ptr<Rays::TransmissionRay> _refract(Rays::Ray* ray, Rays::Hit* hit);
    static double _fresnel(Rays::Ray* ray, Rays::Hit* hit);
    std::array<glm::dvec3, 4> _getWorldspaceCoords(uint32_t i, uint32_t j, uint32_t width, uint32_t height);
    std::unique_ptr<SceneDescription> _scene;
public:
    Renderer();

    explicit Renderer(std::unique_ptr<SceneDescription> scene);
    void render(const std::string& outputFile);
    void render(std::unique_ptr<SceneDescription> scene, const std::string& outputFile);

};


#endif //CS655_RENDERER_H
