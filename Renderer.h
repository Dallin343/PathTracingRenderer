//
// Created by Dallin Hagman on 9/7/21.
//

#ifndef CS655_RENDERER_H
#define CS655_RENDERER_H

#include "Common.h"
#include <random>

#include "Scene/SceneDescription.h"
#include "Lights/Lighting.h"
#include "Scene/BoundingBox.h"


class Renderer {
    inline static std::uniform_real_distribution<double> _distro{0.0, 1.0};
    inline static std::default_random_engine _engine;
    inline static auto _random = std::bind(_distro, _engine);
private:
    std::optional<std::unique_ptr<Rays::Hit>> _findHit(Rays::Ray *ray);
    glm::dvec3 _traceRay(Rays::Ray* ray, uint8_t depth = 0);

    std::unique_ptr<Rays::Ray> _jitter(Rays::Ray* ray);
    std::vector<glm::dvec3> _getWorldspaceCoords(uint32_t i, uint32_t j, uint32_t width, uint32_t height, uint32_t sub);

public:
    Renderer();

    explicit Renderer(std::unique_ptr<SceneDescription> scene);
    void render(const std::string& outputFile);
    void render(std::unique_ptr<SceneDescription> scene, const std::string& outputFile);

private:
    std::unique_ptr<SceneDescription> _scene;
    std::unique_ptr<BoundingBox> _boundingBox;
};


#endif //CS655_RENDERER_H
