//
// Created by Dallin Hagman on 9/7/21.
//

#ifndef CS655_RENDERER_H
#define CS655_RENDERER_H

#include "Common.h"
#include "Scene/SceneDescription.h"
#include <Scene/BoundingBox.h>
#include <array>
#include <random>

const uint8_t MAX_DEPTH = 4;
const int NUM_JITTERS = 4;
const double JITTER_BIAS = 0.1;
const int NUM_THREADS = 12;
const uint32_t SUB_PIXELS = 4;
const int WIDTH = 480;
const int HEIGHT = 480;

class Renderer {
private:
    std::optional<std::unique_ptr<Rays::Hit>> _findHit(Rays::Ray *ray);
    glm::dvec3 _traceRay(Rays::Ray* ray, uint8_t depth = 0);
    glm::dvec3 _calculateIllumination(Rays::Ray* ray, Rays::Hit* hit);

    static std::unique_ptr<Rays::ReflectionRay> _reflect(Rays::Ray* ray, Rays::Hit* hit);
    static std::unique_ptr<Rays::TransmissionRay> _refract(Rays::Ray* ray, Rays::Hit* hit);
    std::unique_ptr<Rays::Ray> _jitter(Rays::Ray* ray);
    static double _fresnel(Rays::Ray* ray, Rays::Hit* hit);
    std::vector<glm::dvec3> _getWorldspaceCoords(uint32_t i, uint32_t j, uint32_t width, uint32_t height, uint32_t sub);

public:
    Renderer();

    explicit Renderer(std::unique_ptr<SceneDescription> scene);
    void render(const std::string& outputFile);
    void render(std::unique_ptr<SceneDescription> scene, const std::string& outputFile);

private:
    std::unique_ptr<SceneDescription> _scene;
    std::unique_ptr<BoundingBox> _boundingBox;
    std::uniform_real_distribution<double> _random{0.0, 1.0};
    std::default_random_engine _randomEngine;
};


#endif //CS655_RENDERER_H
