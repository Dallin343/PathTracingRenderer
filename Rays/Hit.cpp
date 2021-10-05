//
// Created by Dallin Hagman on 9/2/21.
//

#include "Hit.h"

namespace Rays {
    Hit::Hit(double t, const glm::dvec3 &point, const glm::dvec3 &norm, BaseRenderable *object) : _t(t),
                                                                                                  _point(point),
                                                                                                  _norm(norm),
                                                                                                  _object(object) {}

    Hit::Hit(double t, const glm::dvec3 &point, const glm::dvec3 &norm, const glm::dvec2 &texCoords,
             BaseRenderable *object) : _t(t), _point(point), _norm(norm), _texCoords(texCoords), _object(object) {}

    double Hit::getT() const {
        return _t;
    }

    void Hit::setT(double t) {
        _t = t;
    }

    const glm::dvec3 &Hit::getPoint() const {
        return _point;
    }

    void Hit::setPoint(const glm::dvec3 &point) {
        _point = point;
    }

    const glm::dvec3 &Hit::getNorm() const {
        return _norm;
    }

    void Hit::setNorm(const glm::dvec3 &norm) {
        _norm = norm;
    }

    double Hit::distanceTo(const glm::dvec3 &other) {
        return glm::distance(_point, other);
    }

    glm::dvec3 Hit::vectorTo(const glm::dvec3 &other) {
        return glm::normalize(other - _point);
    }

    BaseRenderable *Hit::getObject() const {
        return _object;
    }

    void Hit::setObject(BaseRenderable *object) {
        _object = object;
    }

    const glm::dvec2 &Hit::getTexCoords() const {
        return _texCoords;
    }
}
