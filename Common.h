//
// Created by Dallin Hagman on 9/2/21.
//

#ifndef CS655_COMMON_H
#define CS655_COMMON_H

#include <glm.hpp>


class Bounds {
public:
    glm::dvec3 min, max;

    bool operator^(const Bounds &other) const {
        return 
            (((min.x < other.min.x && other.min.x < max.x) || (other.min.x < min.x && min.x < other.max.x)) &&
            ((min.y < other.min.y && other.min.y < max.y) || (other.min.y < min.y && min.y < other.max.y)) &&
            ((min.z < other.min.z && other.min.z < max.z) || (other.min.z < min.z && min.z < other.max.z))) ||
            (glm::all(glm::greaterThan(min, other.min)) && glm::all(glm::lessThan(max, other.max)));
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
