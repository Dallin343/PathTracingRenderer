//
// Created by Dallin Hagman on 9/7/21.
//

#include <array>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <glm/gtx/vector_angle.hpp>
#include "Renderer.h"

std::string printVec(const glm::dvec3 &vec) {
    std::stringstream stream;
    stream << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return stream.str();
}

void Renderer::render(std::unique_ptr<SceneDescription> scene, const std::string &outputFile) {
    _scene = std::move(scene);
    render(outputFile);
}

std::vector<glm::dvec3> Renderer::_getWorldspaceCoords(uint32_t i, uint32_t j, uint32_t width, uint32_t height, uint32_t sub) {
    glm::dvec2 viewport = _scene->getCamera()->getViewportSize();
    double iStep = (viewport.x * 2.0) / width;
    double jStep = (viewport.y * 2.0) / height;

    double iSubStep = iStep / (double)sub;
    double jSubStep = jStep / (double)sub;

    double uStart = i * iStep - viewport.x;
    double vStart = j * jStep - viewport.y;

    std::vector<glm::dvec3> subPixels;
    subPixels.resize(sub * sub);

    for (int stepI = 0; stepI < sub; stepI++) {
        for (int stepJ = 0; stepJ < sub; stepJ++) {
            // double iJitter = _random(_randomEngine) * iSubStep;
            // double jJitter = _random(_randomEngine) * jSubStep;
            subPixels.emplace_back(uStart + (iSubStep / 2.0) * stepI, vStart + (jSubStep / 2.0) * stepJ, 0.0);
        } 
    }
    // subPixels[0] = glm::dvec3(u - iCorner, v + jCorner, 0.0);
    // subPixels[1] = glm::dvec3(u + iCorner, v + jCorner, 0.0);
    // subPixels[2] = glm::dvec3(u + iCorner, v - jCorner, 0.0);
    // subPixels[3] = glm::dvec3(u - iCorner, v - jCorner, 0.0);
    return subPixels;
}

glm::dvec3 Renderer::_traceRay(Rays::Ray *ray, uint8_t depth) {
    auto closestHit = _findHit(ray);

    if (!closestHit.has_value()) {
        return _scene->getBackground();
    } else if (depth > MAX_DEPTH) {
        return {};
    }

    auto hit = std::move(closestHit.value());
    auto object = hit->getObject();

    const Material *material = object->getMaterial();
    glm::dvec3 color = {0.0, 0.0, 0.0};
    glm::dvec3 reflectiveColor = {0.0, 0.0, 0.0};
    glm::dvec3 transmissionColor = {0.0, 0.0, 0.0};

    switch (material->getType()) {
        case Diffuse:
            color = _calculateIllumination(ray, hit.get());
            if (material->getReflectiveFac() > 0.0) {
                auto reflectionRay = _reflect(ray, hit.get());
                reflectiveColor += _traceRay(reflectionRay.get(), depth + 1);
            }
            color = glm::mix(color, reflectiveColor, material->getReflectiveFac());
            color += _scene->getAmbientColor() * _scene->getAmbientFac() * material->getDiffuseColor();
            break;
        case Transparent:
            if (material->getReflectiveFac() > 0.0) {
                auto reflectionRay = _reflect(ray, hit.get());
                reflectiveColor += _traceRay(reflectionRay.get(), depth + 1);
            }
            if (material->getTransmissionFac() > 0.0) {
                auto transmissionRay = _refract(ray, hit.get());
                transmissionColor += _traceRay(transmissionRay.get(), depth + 1);
            }
            double kr = _fresnel(ray, hit.get());
            color = reflectiveColor * kr + transmissionColor * (1 - kr);
            color = glm::mix(color, reflectiveColor, material->getReflectiveFac());
            break;
    }

    return glm::clamp(color, 0.0, 1.0);
}

void Renderer::render(const std::string &outputFile) {
    const uint32_t subPixels = 2;
    const int width = 480;
    const int height = 480;
    auto image = std::vector<std::vector<glm::ivec3>>();
    image.resize(height);


    const glm::dvec3 from = _scene->getCamera()->getLookFrom();

    _boundingBox = std::make_unique<BoundingBox>(_scene->getRawObjects());
    _boundingBox->subdivide();

    for (uint32_t col = 0; col < width; col++) {
        for (uint32_t row = 0; row < height; row++) {
            auto dirs = _getWorldspaceCoords(col, row, width, height, 2);

            glm::dvec3 color = {0.0, 0.0, 0.0};

            for (const glm::dvec3 &dir: dirs) {
                auto camRay = std::make_unique<Rays::CameraRay>(from, glm::normalize(dir - from));
                color += _traceRay(camRay.get());
            }
            glm::dvec3 avg = color / (double)(subPixels*subPixels);
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

glm::dvec3 Renderer::_calculateIllumination(Rays::Ray *ray, Rays::Hit *hit) {
    BaseRenderable *object = hit->getObject();
    auto material = object->getMaterial();
    glm::dvec3 color = {0.0, 0.0, 0.0};
    auto &lights = _scene->getLights();

    for (const auto& light : lights) {
        if (!light->inShadow(ray, hit, _scene->getObjects())) {
            glm::dvec3 diffuse = light->calculateDiffuse(ray, hit, material, _scene->getObjects());
            glm::dvec3 specular = light->calculateSpecular(ray, hit, material, _scene->getObjects(),
                                                           _scene->getCamera());

            // TEMPORARY
            color += diffuse + specular;
        }
    }

    return color;
}

std::optional<std::unique_ptr<Rays::Hit>> Renderer::_findHit(Rays::Ray *ray) {
    return _boundingBox->intersect(ray);
//    std::optional<std::unique_ptr<Rays::Hit>> closestHit = std::nullopt;
//    for (const auto &object: _scene->getObjects()) {
//        std::optional<std::unique_ptr<Rays::Hit>> hit = object->intersect(ray);
//        if (!hit.has_value()) {
//            continue;
//        }
//
//        if (!closestHit.has_value()) {
//            closestHit = std::move(hit);
//        } else if (hit.value()->distanceTo(ray->getOrigin()) < closestHit.value()->distanceTo(ray->getOrigin())) {
//            closestHit = std::move(hit);
//        }
//    }
//    return closestHit;
}

std::unique_ptr<Rays::ReflectionRay> Renderer::_reflect(Rays::Ray *ray, Rays::Hit *hit) {
    double e = 0.00001;
    auto currentDir = ray->getDirection();
    auto norm = hit->getNorm();
    glm::dvec3 reflectionDir = glm::normalize(currentDir - norm * 2.0 * glm::dot(currentDir, norm));

    glm::dvec3 bias = glm::dot(currentDir, norm) < 0.0 ? norm * e : norm * -e;
    return std::make_unique<Rays::ReflectionRay>(hit->getPoint() + bias, reflectionDir);
}

std::unique_ptr<Rays::TransmissionRay> Renderer::_refract(Rays::Ray *ray, Rays::Hit *hit) {
    double e = 1e-8;
    glm::dvec3 I = ray->getDirection();
    glm::dvec3 N = hit->getNorm();
    double ior = hit->getObject()->getMaterial()->getIor();

    double cosi = glm::clamp(glm::dot(I, N), -1.0, 1.0);
    double n1 = 1.0, n2 = ior;
    glm::dvec3 n = N;
    if (cosi < 0) { cosi = -cosi; } else { std::swap(n1, n2); n= -N; }
    double eta = n1 / n2;
    double k = 1 - eta * eta * (1 - cosi * cosi);
    glm::dvec3 refractDir = k < 0.0 ? glm::dvec3() : eta * I + (eta * cosi - glm::sqrt(k)) * n;
    refractDir = glm::normalize(refractDir);

    bool outside = glm::dot(I, N) < 0;
    glm::dvec3 bias = e * N;
    glm::dvec3 origin = outside ? hit->getPoint() - bias : hit->getPoint() + bias;
    return std::make_unique<Rays::TransmissionRay>(origin, refractDir);
}

double Renderer::_fresnel(Rays::Ray *ray, Rays::Hit *hit) {
    glm::dvec3 I = ray->getDirection();
    glm::dvec3 N = hit->getNorm();
    double ior = hit->getObject()->getMaterial()->getIor();

    double cosi = glm::clamp(glm::dot(I, N), -1.0, 1.0);
    double etai = 1, etat = ior;
    if (cosi > 0) { std::swap(etai, etat); }
    // Compute sini using Snell's law
    double sint = etai / etat * glm::sqrt(glm::max(0.0, 1 - cosi * cosi));
    // Total internal reflection
    if (sint >= 1) {
        return 1;
    }
    else {
        double cost = glm::sqrt(glm::max(0.0, 1 - sint * sint));
        cosi = glm::abs(cosi);
        double Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
        double Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
        return (Rs * Rs + Rp * Rp) / 2.0;
    }
}

Renderer::Renderer() = default;

