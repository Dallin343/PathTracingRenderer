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
        bool minInside = glm::any(glm::greaterThanEqual(min, other.min)) && glm::any(glm::lessThanEqual(min, other.max));
        bool maxInside = glm::any(glm::greaterThanEqual(max, other.min)) && glm::any(glm::lessThanEqual(max, other.max));
        return minInside || maxInside;
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
