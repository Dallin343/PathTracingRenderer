//
// Created by Dallin Hagman on 9/2/21.
//

#include "Hit.h"

Rays::Hit::Hit(double t, const glm::dvec3 &point, const glm::dvec3 &norm) : _t(t), _point(point), _norm(norm) {}

double Rays::Hit::getT() const {
    return _t;
}

void Rays::Hit::setT(double t) {
    _t = t;
}

const glm::dvec3 &Rays::Hit::getPoint() const {
    return _point;
}

void Rays::Hit::setPoint(const glm::dvec3 &point) {
    _point = point;
}

const glm::dvec3 &Rays::Hit::getNorm() const {
    return _norm;
}

void Rays::Hit::setNorm(const glm::dvec3 &norm) {
    _norm = norm;
}
