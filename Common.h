//
// Created by Dallin Hagman on 9/2/21.
//

#ifndef CS655_COMMON_H
#define CS655_COMMON_H

#include <glm.hpp>
#include <algorithm>
#include <memory>
#include <vector>
#include <unordered_map>
#include <optional>
#include <Debug/Instrumentor.h>
#include <random>

#define GI true

const uint8_t MAX_DEPTH = 4;
const int NUM_JITTERS = 2;
const double JITTER_BIAS = 0.1;
const int NUM_THREADS = 1;
const uint32_t SUB_PIXELS = 2;
const int WIDTH = 480;
const int HEIGHT = 480;
const int PATH_SAMPLES = 4;

class Util {
public:
    inline static std::uniform_real_distribution<double> _distro{0.0, 1.0};
    inline static std::default_random_engine _engine;
    inline static auto _random = std::bind(_distro, _engine);
};

const glm::dmat3 WORLD_BASIS = {
        {1.0, 0.0, 0.0},
        {0.0, 1.0, 0.0},
        {0.0, 0.0, -1.0}
};

const double BIAS = 1e-6;
const int NUM_SHADOW_SAMPLES = 20;

class Bounds {
public:
    glm::dvec3 min, max;

    bool operator^(const Bounds &other) const {
        return
            (((min.x <= other.min.x && other.min.x <= max.x) || (other.min.x <= min.x && min.x <= other.max.x)) &&
            ((min.y <= other.min.y && other.min.y <= max.y) || (other.min.y <= min.y && min.y <= other.max.y)) &&
            ((min.z <= other.min.z && other.min.z <= max.z) || (other.min.z <= min.z && min.z <= other.max.z))) ||
            (glm::all(glm::greaterThanEqual(min, other.min)) && glm::all(glm::lessThanEqual(max, other.max)));
    }

    glm::bvec3 operator>(const Bounds &other) const {
        return glm::greaterThan(max, other.max);
    }

    glm::bvec3 operator<(const Bounds &other) const {
        return glm::lessThan(min, other.min);
    }

    double x() {
        return glm::abs(max.x - min.x);
    }

    double y() {
        return glm::abs(max.y - min.y);
    }

    double z() {
        return glm::abs(max.z - min.z);
    }
};

#endif //CS655_COMMON_H
