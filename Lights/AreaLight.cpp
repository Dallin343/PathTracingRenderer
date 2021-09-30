#include "AreaLight.h"

namespace AreaLight {

    AreaLight(const glm::dvec3 &pos, const glm::dvec3 &u, const glm::dvec3 &v,
            double w, double h, const glm::dvec3 &col, double intensity)
        : Light(pos, col), _u(glm::normalize(u)), _v(glm::normalize(v)), _width(w),
        _height(h) {}

    std::vector<glm::dvec3> getSamplePositions() const {
        std::vector<glm::dvec3> samples;
        samples.reserve(NUM_SHADOW_SAMPLES * NUM_SHADOW_SAMPLES);

        double uStep = _width / NUM_SHADOW_SAMPLES;
        double vStep = _height / NUM_SHADOW_SAMPLES;

        for (int i = 0; i < NUM_SHADOW_SAMPLES; i++) {
            for (int j = 0; j < NUM_SHADOW_SAMPLES; j++) {
            double randU = uStep * _random(_engine);
            double randV = vStep * _random(_engine);

            samples.emplace_back((_position + (_u * i)) + randU, (_position + (_v * j)) + randV);
            }
        }
        return samples;
    }
} // namespace AreaLight