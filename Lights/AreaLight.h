#pragma once

#include "Light.h"
#include <random>

class AreaLight : public Light {
    inline static std::uniform_real_distribution<double> _distro{0.0, 1.0};
    inline static std::default_random_engine _engine;
    inline static auto _random = std::bind(_distro, _engine);
private:
    glm::dvec3 _u, _v;
    double _width, _height;
public:
    AreaLight(const glm::dvec3&, const glm::dvec3&, const glm::dvec3&, double, double, const glm::dvec3&, double);
    virtual std::vector<glm::dvec3> getSamplePositions() const override;
};