//
// Created by Dallin Hagman on 9/7/21.
//

#include <array>
#include <algorithm>
#include <fstream>
#include "Renderer.h"

void Renderer::render(std::unique_ptr<SceneDescription> scene, const std::string &outputFile) {
    _scene = std::move(scene);
    render(outputFile);
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
//    subPixels[0] = {u, v, 0.0};
//    return subPixels;
    subPixels[0] = glm::dvec3(u - iCorner, v + jCorner, 0.0);
    subPixels[1] = glm::dvec3(u + iCorner, v + jCorner, 0.0);
    subPixels[2] = glm::dvec3(u + iCorner, v - jCorner, 0.0);
    subPixels[3] = glm::dvec3(u - iCorner, v - jCorner, 0.0);
    return subPixels;
}

glm::dvec3 Renderer::_traceRay(Rays::Ray *ray, uint8_t depth = 0) {
    std::vector<std::pair<const std::unique_ptr<BaseRenderable> &, std::unique_ptr<Rays::Hit>>> hits;
    for (const auto &object: _scene->getObjects()) {
        std::optional<std::unique_ptr<Rays::Hit>> hit = object->Intersect(ray);
        if (hit.has_value()) {
            hits.emplace_back(object, std::move(hit.value()));
        }
    }

    if (hits.empty()) {
        return _scene->getBackground();
    }

    double min = -1.0;
    int closest;
    for (int i = 0; i < hits.size(); i++) {
        auto &pair = hits.at(i);
        auto distance = pair.second->distanceTo(ray->getOrigin());
        if (distance < min || min == -1) {
            min = distance;
            closest = i;
        }
    }
    auto &found = hits.at(closest);
    auto &object = found.first;
    auto hit = std::move(found.second);

    const Material* material = object->GetMaterial();
    glm::dvec3 finalColor = {0.0, 0.0, 0.0};
    glm::dvec3 reflectiveColor = {0.0, 0.0, 0.0};

    // Reflection Rays
    auto currentDir = ray->getDirection();
    auto nrm = hit->getNorm();
    double e = 0.0001;

    if (material->getReflectiveFac() > 0.0 && depth < MAX_DEPTH) {
        glm::dvec3 reflectionDir = glm::normalize(currentDir - nrm * 2.0 * glm::dot(currentDir, nrm));
        auto reflectionRay = std::make_unique<Rays::CameraRay>(hit->getPoint() + nrm * e, reflectionDir);
        reflectiveColor += _traceRay(reflectionRay.get(), depth + 1);
    }

    auto &lights = _scene->getLights();

    std::for_each(lights.begin(), lights.end(), [&](const std::unique_ptr<Light> &light) {
        glm::dvec3 diffuse = light->calculateDiffuse(ray, hit.get(), material, _scene->getObjects());
        glm::dvec3 specular = light->calculateSpecular(ray, hit.get(), material, _scene->getObjects(), _scene->getCamera());

        // TEMPORARY
        finalColor += diffuse + specular;
    });

    finalColor += _scene->getAmbientColor() * material->getDiffuseColor() * _scene->getAmbientFac();

    finalColor = glm::mix(finalColor, reflectiveColor, material->getReflectiveFac());
    return glm::clamp(finalColor, 0.0, 1.0);
}

glm::dvec3 Renderer::_traceRay(Rays::IlluminationRay *ray) {
    return glm::dvec3();
}

void Renderer::render(const std::string &outputFile) {
    const int width = 480;
    const int height = 480;
    auto image = std::vector<std::vector<glm::ivec3>>();
    image.resize(height);


    const glm::dvec3 from = _scene->getCamera()->getLookFrom();

    for (uint32_t col = 0; col < width; col++) {
        for (uint32_t row = 0; row < height; row++) {
            auto dirs = _getWorldspaceCoords(col, row, width, height);

            glm::dvec3 color = {0.0, 0.0, 0.0};
//            auto camRay = std::make_unique<Rays::CameraRay>(from, glm::normalize(dirs[0] - from));
//            color += _traceRay(camRay.get(), 0);
            for (const glm::dvec3 &dir: dirs) {
                std::unique_ptr<Rays::Ray> camRay = std::make_unique<Rays::CameraRay>(from, glm::normalize(dir - from));
//                std::cout <<"("<<camRay->getDirection().x<<","<<camRay->getDirection().y<<","<< camRay->getDirection().z<<") ";
                color += _traceRay(camRay.get(), 0);
            }
//            std::cout << std::endl;
            glm::dvec3 avg = color / 4.0;
            image.at(col).push_back(glm::ivec3(int(avg.x * 255.0), int(avg.y * 255.0), int(avg.z * 255.0)));
        }
    }

    std::ofstream stream(outputFile);

    stream << "P3" << std::endl << width << " " << height << std::endl << "255" << std::endl;
    for (const auto &row: image) {
        for (const auto &col: row) {
            stream << col.x << " " << col.y << " " << col.z << " ";
        }
        stream << std::endl;
    }
    stream.close();
}


Renderer::Renderer(std::unique_ptr<SceneDescription> scene) {
    this->_scene = std::move(scene);
}

Renderer::Renderer() = default;

