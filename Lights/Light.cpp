//
// Created by Dallin Hagman on 9/2/21.
//

#include "Light.h"

namespace Light {
    Light(const glm::dvec3 &position, const glm::dvec3 &color, double intensity) : _position(position), _color(color), _intensity(intensity) {}

    const glm::dvec3 &getPosition() const {
        return _position;
    }

    void setPosition(const glm::dvec3 &position) {
        _position = position;
    }

    const glm::dvec3 &getColor() const {
        return _color;
    }

    void setColor(const glm::dvec3 &color) {
        _color = color;
    }

    double attenuate(const glm::dvec3& origin, const glm::dvec3& lightPos) const {
        double d = glm::distance(lightPos, origin);
        return _intensity / (4 * M_PI * d*d);
    }

    std::vector<glm::dvec3> getSamplePositions() const {
        return {_position};
    }
}
