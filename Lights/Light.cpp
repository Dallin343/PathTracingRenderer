//
// Created by Dallin Hagman on 9/2/21.
//

#include "Light.h"

Light::Light(const glm::dvec3 &position, const glm::dvec3 &color) : _position(position), _color(color) {}

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

bool Light::_inShadow(const Rays::IlluminationRay *ray, const std::vector<std::unique_ptr<BaseRenderable>> &objects) {
    for (const auto& object : objects) {
        auto hit = object->Intersect(ray);
        if (hit.has_value()) {
            return true;
        }
    }
    return false;
}
