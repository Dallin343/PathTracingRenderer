//
// Created by Dallin Hagman on 9/7/21.
//

#ifndef CS655_RENDERER_H
#define CS655_RENDERER_H

#include "Scene/SceneDescription.h"
#include <array>

const uint8_t MAX_DEPTH = 10;

class Renderer {
private:
    glm::dvec3 _traceRay(const std::shared_ptr<Rays::CameraRay>& ray, uint8_t depth);
    glm::dvec3 _traceRay(std::shared_ptr<Rays::IlluminationRay> ray);
    std::array<glm::dvec3, 4> _getWorldspaceCoords(uint32_t i, uint32_t j, uint32_t width, uint32_t height);
    std::shared_ptr<SceneDescription> _scene;
public:
    void render(const std::shared_ptr<SceneDescription>& scene, const std::string& outputFile);
};


#endif //CS655_RENDERER_H
