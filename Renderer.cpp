//
// Created by Dallin Hagman on 9/7/21.
//

#include "Renderer.h"
#include <sstream>
#include <thread>

std::string printVec(const glm::dvec3 &vec)
{
    std::stringstream stream;
    stream << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return stream.str();
}


Renderer::Renderer() = default;

Renderer::Renderer(std::unique_ptr<SceneDescription> scene)
{
    this->_scene = std::move(scene);
}

void Renderer::render(std::unique_ptr<SceneDescription> scene, const std::string &outputFile)
{
    PROFILE_FUNCTION();
    _scene = std::move(scene);
    render(outputFile);
}

std::vector<glm::dvec3>
Renderer::_getWorldspaceCoords(uint32_t i, uint32_t j, uint32_t width, uint32_t height, uint32_t sub)
{
    PROFILE_FUNCTION();
    glm::dvec2 viewport = _scene->getCamera()->getViewportSize();
    double iStep = (viewport.x * 2.0) / width;
    double jStep = (viewport.y * 2.0) / height;

    double iSubStep = iStep / (double) sub;
    double jSubStep = jStep / (double) sub;

    double uStart = i * iStep - viewport.x;
    double vStart = j * jStep - viewport.y;

    std::vector<glm::dvec3> subPixels;
    subPixels.reserve(sub * sub);

    for (int stepI = 0; stepI < sub; stepI++) {
        double currI = uStart + iSubStep * stepI;
        for (int stepJ = 0; stepJ < sub; stepJ++) {
            double currJ = vStart + jSubStep * stepJ;
            double iJitter = Renderer::_random() * iSubStep;
            double jJitter = Renderer::_random() * jSubStep;
            subPixels.emplace_back(currI + iJitter, currJ + jJitter, 0.0);
        }
    }
    return subPixels;
}

glm::dvec3 Renderer::_traceRay(Rays::Ray *ray, uint8_t depth)
{
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
        case Textured:
        case Diffuse:
            PROFILE_SCOPE("Diffuse Tracing");
            color = Lighting::calculateIllumination(ray, hit.get(), material, _scene.get());
            if (material->getReflectiveFac() > 0.0) {
                PROFILE_SCOPE("Reflection");
                auto reflectionRay = Lighting::reflect(ray, hit.get());
                if (material->getGlossyFac() > 0.0) {
                    glm::dvec3 tempColor = {};
                    for (int i = 0; i < NUM_JITTERS; i++) {
                        tempColor += _traceRay(_jitter(reflectionRay.get()).get(), depth + 1);
                    }
                    reflectiveColor += tempColor / (double) NUM_JITTERS;
                } else {
                    reflectiveColor += _traceRay(reflectionRay.get(), depth + 1);
                }
            }
            color = glm::mix(color, reflectiveColor, material->getReflectiveFac());

            if (material->getType() == Textured) {
                auto texColor = material->getTexture()->linear(hit->getTexCoords());
                color += _scene->getAmbientColor() * _scene->getAmbientFac() * texColor;
            } else {
                color += _scene->getAmbientColor() * _scene->getAmbientFac() * material->getDiffuseColor();
            }
            break;
        case Transparent: {
            PROFILE_SCOPE("Transparent Tracing");
            if (material->getReflectiveFac() > 0.0) {
                PROFILE_SCOPE("Reflection");
                auto reflectionRay = Lighting::reflect(ray, hit.get());
                if (material->getGlossyFac() > 0.0) {
                    glm::dvec3 tempColor = {};
                    for (int i = 0; i < NUM_JITTERS; i++) {
                        tempColor += _traceRay(_jitter(reflectionRay.get()).get(), depth + 1);
                    }
                    reflectiveColor += tempColor / (double) NUM_JITTERS;
                } else {
                    reflectiveColor += _traceRay(reflectionRay.get(), depth + 1);
                }
            }
            if (material->getTransmissionFac() > 0.0) {
                PROFILE_SCOPE("Transmission");
                auto transmissionRay = Lighting::refract(ray, hit.get());
                if (material->getTranslucencyFac() > 0.0) {
                    glm::dvec3 tempColor = {};
                    for (int i = 0; i < NUM_JITTERS; i++) {
                        tempColor += _traceRay(_jitter(transmissionRay.get()).get(), depth + 1);
                    }
                    transmissionColor += tempColor / (double) NUM_JITTERS;
                } else {
                    transmissionColor += _traceRay(transmissionRay.get(), depth + 1);
                }
            }
            double kr = Lighting::fresnel(ray, hit.get());
            color = reflectiveColor * kr + transmissionColor * (1 - kr);
            color = glm::mix(color, reflectiveColor, material->getReflectiveFac());
            break;
        }
    }

    return glm::clamp(color, 0.0, 1.0);
}

void Renderer::render(const std::string &outputFile)
{
    PROFILE_FUNCTION();

    auto image = std::vector<std::vector<glm::ivec3>>();
    image.resize(HEIGHT);

    int threadInc = HEIGHT / NUM_THREADS;

    std::vector<std::thread> threads;

    const glm::dvec3 from = _scene->getCamera()->getLookFrom();

    _boundingBox = std::make_unique<BoundingBox>(_scene->getRawObjects());
    _boundingBox->subdivide();

    auto loop = [&](int start, int end)
    {
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

    for (auto &t: threads) {
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


std::optional<std::unique_ptr<Rays::Hit>> Renderer::_findHit(Rays::Ray *ray)
{
    return _boundingBox->intersect(ray);
}

std::unique_ptr<Rays::Ray> Renderer::_jitter(Rays::Ray *ray)
{
    auto x = Renderer::_random() * JITTER_BIAS;
    auto y = Renderer::_random() * JITTER_BIAS;
    auto z = Renderer::_random() * JITTER_BIAS;
    glm::dvec3 rand = {x, y, z};
    return std::make_unique<Rays::Ray>(ray->getOrigin(), glm::normalize(ray->getDirection() + rand));
}


