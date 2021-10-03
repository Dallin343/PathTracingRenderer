//
// Created by Dallin Hagman on 9/2/21.
//

#include "Light.h"

Light::Light(const glm::dvec3 &position, const glm::dvec3 &color, double intensity) : _position(position), _color(color), _intensity(intensity) {}

const glm::dvec3 &Light::getPosition() const {
    return _position;
}

void Light::setPosition(const glm::dvec3 &position) {
    _position = position;
}

const glm::dvec3 &Light::getColor() const {
    return _color;
}

void Light::setColor(const glm::dvec3 &color) {
    _color = color;
}

double Light::attenuate(const glm::dvec3& origin, const glm::dvec3& lightPos) const {
    double d = glm::distance(lightPos, origin);
    return _intensity / (4 * M_PI * d*d);
}

std::vector<glm::dvec3> Light::getSamplePositions() const {
    return {_position};
}