//
// Created by Dallin Hagman on 9/7/21.
//

#include <array>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <glm/gtx/vector_angle.hpp>
#include "Renderer.h"
#include <thread>

std::string printVec(const glm::dvec3 &vec) {
    std::stringstream stream;
    stream << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return stream.str();
}

void Renderer::render(std::unique_ptr<SceneDescription> scene, const std::string &outputFile) {
    PROFILE_FUNCTION();
    _scene = std::move(scene);
    render(outputFile);
}

std::vector<glm::dvec3> Renderer::_getWorldspaceCoords(uint32_t i, uint32_t j, uint32_t width, uint32_t height, uint32_t sub) {
    PROFILE_FUNCTION();
    glm::dvec2 viewport = _scene->getCamera()->getViewportSize();
    double iStep = (viewport.x * 2.0) / width;
    double jStep = (viewport.y * 2.0) / height;

    double iSubStep = iStep / (double)sub;
    double jSubStep = jStep / (double)sub;

    double uStart = i * iStep - viewport.x;
    double vStart = j * jStep - viewport.y;

    std::vector<glm::dvec3> subPixels;
    subPixels.reserve(sub * sub);

    for (int stepI = 0; stepI < sub; stepI++) {
        double currI = uStart + iSubStep * stepI;
        for (int stepJ = 0; stepJ < sub; stepJ++) {
            double currJ = vStart + jSubStep * stepJ;
             double iJitter = _random(_randomEngine) * iSubStep;
             double jJitter = _random(_randomEngine) * jSubStep;
            subPixels.emplace_back(currI + iJitter, currJ + jJitter, 0.0);
        }
    }
    return subPixels;
}

glm::dvec3 Renderer::_traceRay(Rays::Ray *ray, uint8_t depth) {
    PROFILE_FUNCTION();
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
        case Diffuse: {
            PROFILE_SCOPE("Diffuse Tracing");
            color = _calculateIllumination(ray, hit.get());
            if (material->getReflectiveFac() > 0.0) {
                PROFILE_SCOPE("Reflection");
                auto reflectionRay = _reflect(ray, hit.get());
                if (material->getGlossyFac() > 0.0) {
                    glm::dvec3 tempColor = {};
                    for (int i = 0; i < NUM_JITTERS; i++) {
                        tempColor += _traceRay(_jitter(reflectionRay.get()).get(), depth + 1);
                    }
                    reflectiveColor += tempColor / (double)NUM_JITTERS;
                } else {
                    reflectiveColor += _traceRay(reflectionRay.get(), depth + 1);
                }
            }
            color = glm::mix(color, reflectiveColor, material->getReflectiveFac());
            color += _scene->getAmbientColor() * _scene->getAmbientFac() * material->getDiffuseColor();
            break;
        }
        case Transparent: {
            PROFILE_SCOPE("Transparent Tracing");
            if (material->getReflectiveFac() > 0.0) {
                PROFILE_SCOPE("Reflection");
                auto reflectionRay = _reflect(ray, hit.get());
                if (material->getGlossyFac() > 0.0) {
                    glm::dvec3 tempColor = {};
                    for (int i = 0; i < NUM_JITTERS; i++) {
                        tempColor += _traceRay(_jitter(reflectionRay.get()).get(), depth + 1);
                    }
                    reflectiveColor += tempColor / (double)NUM_JITTERS;
                } else {
                    reflectiveColor += _traceRay(reflectionRay.get(), depth + 1);
                }
            }
            if (material->getTransmissionFac() > 0.0) {
                PROFILE_SCOPE("Transmission");
                auto transmissionRay = _refract(ray, hit.get());
                if (material->getTranslucencyFac() > 0.0) {
                    glm::dvec3 tempColor = {};
                    for (int i = 0; i < NUM_JITTERS; i++) {
                        tempColor += _traceRay(_jitter(transmissionRay.get()).get(), depth + 1);
                    }
                    transmissionColor += tempColor / (double)NUM_JITTERS;
                } else {
                    transmissionColor += _traceRay(transmissionRay.get(), depth + 1);
                }
            }
            double kr = _fresnel(ray, hit.get());
            color = reflectiveColor * kr + transmissionColor * (1 - kr);
            color = glm::mix(color, reflectiveColor, material->getReflectiveFac());
            break;
        }
    }

    return glm::clamp(color, 0.0, 1.0);
}

void Renderer::render(const std::string &outputFile) {
    PROFILE_FUNCTION();

    auto image = std::vector<std::vector<glm::ivec3>>();
    image.resize(HEIGHT);

    int threadInc = HEIGHT / NUM_THREADS;

    std::vector<std::thread> threads;

    const glm::dvec3 from = _scene->getCamera()->getLookFrom();

    _boundingBox = std::make_unique<BoundingBox>(_scene->getRawObjects());
    _boundingBox->subdivide();

    auto loop = [&](int start, int end) {
        for (uint32_t row = start; row < end; row++) {
            for (uint32_t col = 0; col < WIDTH; col++) {
                auto dirs = _getWorldspaceCoords(row, col, WIDTH, HEIGHT, SUB_PIXELS);

                glm::dvec3 color = {0.0, 0.0, 0.0};

                for (const glm::dvec3 &dir: dirs) {
                    auto camRay = std::make_unique<Rays::CameraRay>(from, glm::normalize(dir - from));
                    color += _traceRay(camRay.get());
                }
                glm::dvec3 avg = color / (double) (SUB_PIXELS * SUB_PIXELS);
                image.at(row).push_back(glm::ivec3(int(avg.x * 255.0), int(avg.y * 255.0), int(avg.z * 255.0)));
            }
        }
    };

    int start = 0;
    while (start + threadInc <= HEIGHT) {
        threads.emplace_back(loop, start, std::min(start + threadInc, HEIGHT));
        start += threadInc;
    }

    for (auto& t : threads) {
        t.join();
    }

    std::ofstream stream(outputFile);

    {
        PROFILE_SCOPE("Writing");
        stream << "P3" << std::endl << WIDTH << " " << HEIGHT << std::endl << "255" << std::endl;
        for (const auto &row: image) {
            for (const auto &col: row) {
                stream << col.x << " " << col.y << " " << col.z << " ";
            }
            stream << std::endl;
        }
        stream.close();
    }
}


Renderer::Renderer(std::unique_ptr<SceneDescription> scene) {
    this->_scene = std::move(scene);
}

glm::dvec3 Renderer::_calculateIllumination(Rays::Ray *ray, Rays::Hit *hit) {
    PROFILE_FUNCTION();
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

std::unique_ptr<Rays::Ray> Renderer::_jitter(Rays::Ray *ray) {
    auto x = _random(_randomEngine) * JITTER_BIAS;
    auto y = _random(_randomEngine) * JITTER_BIAS;
    auto z = _random(_randomEngine) * JITTER_BIAS;
    glm::dvec3 rand = {x, y, z};
    return std::make_unique<Rays::Ray>(ray->getOrigin(), glm::normalize(ray->getDirection() + rand));
}

Renderer::Renderer() = default;

