//
// Created by Dallin Hagman on 9/7/21.
//

#include <array>
#include "Renderer.h"

void Renderer::render(const std::shared_ptr<SceneDescription> &scene, const std::string &outputFile) {
    _scene = scene;
    auto image = std::array<std::array<glm::dvec3, 480>, 480>();

    const glm::dvec3 from = _scene->getCamera()->getLookFrom();

    for (uint32_t col = 0; col < 1000; col++) {
        for (uint32_t row = 0; row < 1000; row++) {
            auto dirs = _getWorldspaceCoords(col, row, 1000, 1000);

            glm::dvec3 color = {0.0, 0.0, 0.0};
            for (const glm::dvec3 &dir: dirs) {
                auto camRay = std::make_shared<Rays::CameraRay>(from, glm::normalize(dir - from));
                color += _traceRay(camRay, 0);
            }
            image[row][col] = color / 4.0;
        }
    }
}

std::array<glm::dvec3, 4> Renderer::_getWorldspaceCoords(uint32_t i, uint32_t j, uint32_t width, uint32_t height) {
    glm::dvec2 viewport = _scene->getCamera()->getViewportSize();
    double iStep = (viewport.x * 2.0) / width;
    double jStep = (viewport.y * 2.0) / height;
    double iCorner = iStep / 4.0;
    double jCorner = jStep / 4.0;

    double u = i * iStep + (iStep / 2.0) - viewport.x;
    double v = j * jStep + (jStep / 2.0) - viewport.y;

    auto subPixels = std::array<glm::dvec3, 4>();
    subPixels[0] = glm::dvec3(u - iCorner, v + jCorner, 0.0);
    subPixels[1] = glm::dvec3(u + iCorner, v + jCorner, 0.0);
    subPixels[2] = glm::dvec3(u + iCorner, v - jCorner, 0.0);
    subPixels[3] = glm::dvec3(u - iCorner, v - jCorner, 0.0);
    return subPixels;
}

glm::dvec3 Renderer::_traceRay(const std::shared_ptr<Rays::CameraRay> &ray, uint8_t depth = 0) {
    std::vector<std::pair<std::shared_ptr<BaseRenderable>, std::shared_ptr<Rays::Hit>>> hits;
    for (const auto &object: _scene->getObjects()) {
        std::optional<std::shared_ptr<Rays::Hit>> hit = object->Intersect(ray);
        hits.emplace_back(object, hit.value());
    }

    if (hits.empty()) {
        return _scene->getBackground();
    }

    double min = -1.0;
    std::pair<std::shared_ptr<BaseRenderable>, std::shared_ptr<Rays::Hit>> closest;
    for (const auto &pair: hits) {
        auto distance = pair.second->distanceTo(ray->getOrigin());
        if (distance < min || min == -1) {
            min = distance;
            closest = pair;
        }
    }

    auto object = closest.first;
    auto hit = closest.second;

    std::shared_ptr<Material> material = closest.first->GetMaterial();
    glm::dvec3 finalColor = {0.0, 0.0, 0.0};
    glm::dvec3 reflectiveColor = {0.0, 0.0, 0.0};

    // Reflection Rays
    auto currentDir = ray->getDirection();
    auto nrm = hit->getNorm();
    double e = 0.00001;

    if (depth < MAX_DEPTH) {
        glm::dvec3 reflectionDir = glm::normalize(currentDir - nrm * 2.0 * glm::dot(currentDir, nrm));
        auto reflectionRay = std::make_shared<Rays::CameraRay>(hit->getPoint() + nrm * e, reflectionDir);
        reflectiveColor += _traceRay(reflectionRay, depth + 1);
    }

    std::vector<std::shared_ptr<Light>> lights = _scene->getLights();

    std::for_each(lights.begin(),  lights.end(), [&](const std::shared_ptr<Light>& light) {
        glm::dvec3 diffuse = light->calculateDiffuse(ray, hit, material, _scene);
        glm::dvec3 specular = light->calculateSpecular(ray, hit, material, _scene);

        // TEMPORARY
        finalColor += diffuse + specular;
    });

    return finalColor;
}

glm::dvec3 Renderer::_traceRay(std::shared_ptr<Rays::IlluminationRay> ray) {
    return glm::dvec3();
}

