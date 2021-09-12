//
// Created by Dallin Hagman on 9/2/21.
//

#include "Ray.h"
namespace Rays {
    Ray::Ray(const glm::dvec3 &origin, const glm::dvec3 &direction) : _origin(origin), _direction(direction) {}

    const glm::dvec3 &Ray::getOrigin() const {
        return _origin;
    }

    void Ray::setOrigin(const glm::dvec3 &origin) {
        _origin = origin;
    }

    const glm::dvec3 &Ray::getDirection() const {
        return _direction;
    }

    void Ray::setDirection(const glm::dvec3 &direction) {
        _direction = direction;
    }
}
