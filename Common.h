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
        return glm::all(glm::greaterThan(min, other.min)) and glm::all(glm::lessThan(max, other.max));
    }

    bool operator>(const Bounds &other) const {
        return glm::all(glm::greaterThan(max, other.max));
    }

    bool operator<(const Bounds &other) const {
        return glm::all(glm::lessThan(min, other.min));
    }
};

#endif //CS655_COMMON_H
