#pragma once

#include "Light.h"
#include <random>

class AreaLight : public Light {
private:
    glm::dvec3 _u, _v;
    double _width, _height;
    std::uniform_real_distribution<double> _random{0.0, 1.0};
    std::default_random_engine _engine;
public:
    AreaLight(const glm::dvec3&, const glm::dvec3&, const glm::dvec3&, double, double, const glm::dvec3&, double);
    virtual std::vector<glm::dvec3> getSamplePositions() const override;

}