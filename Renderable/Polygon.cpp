//
// Created by Dallin Hagman on 9/14/21.
//

#include <algorithm>
#include "Polygon.h"

Polygon::Polygon(const std::unique_ptr<Material> &material, std::vector<glm::dvec3> vertices) :
    BaseRenderable(material), _vertices(std::move(vertices)), _projVertices({}) {

    glm::dvec3 v1 = _vertices.at(2) - _vertices.at(0);
    glm::dvec3 v2 = _vertices.at(1) - _vertices.at(0);
    _normal = glm::cross(v1, v2);
    _d = glm::dot(_vertices.at(2), _normal);

    _projVertices.resize(_vertices.size());
    auto absNormal = glm::abs(_normal);

    auto transform = [&](glm::dvec3& v) {
        if (absNormal.x > absNormal.y && absNormal.x > absNormal.z) {
            return glm::dvec2(v.y, v.z);
        } else if (absNormal.y > absNormal.x && absNormal.y > absNormal.z) {
            return glm::dvec2(v.x, v.z);
        } else {
            return glm::dvec2(v.x,v.y);
        }
    };

    std::transform(_vertices.begin(), _vertices.end(), std::back_inserter(_projVertices), transform);
}

std::optional<std::unique_ptr<Rays::Hit>> Polygon::intersect(const Rays::Ray *ray) {
    //Refactor into Plane -> Polygon
    auto hit = planeIntersect(ray);
    if (!hit.has_value()) {
        return std::nullopt;
    }
    glm::dvec3 hitPoint = hit.value()->getPoint();
    glm::dvec2 projHit;
    auto absNormal = glm::abs(_normal);
    if (absNormal.x > absNormal.y && absNormal.x > absNormal.z) {
        projHit = {hitPoint.y, hitPoint.z};
    } else if (absNormal.y > absNormal.x && absNormal.y > absNormal.z) {
        projHit = {hitPoint.x, hitPoint.z};
    } else {
        projHit = {hitPoint.x, hitPoint.y};
    }

    std::vector<glm::dvec2> translatedPoints;
    return std::nullopt;
}

const Material *Polygon::getMaterial() {
    return _material.get();
}

std::optional<std::unique_ptr<Rays::Hit>> Polygon::planeIntersect(const Rays::Ray *ray) {
    const glm::dvec3 dir = ray->getDirection();
    const glm::dvec3 origin = ray->getOrigin();
    double vd = glm::dot(_normal, ray->getDirection());
    if (vd == 0) {
        return std::nullopt;
    }

    double vo = -(glm::dot(_normal, ray->getOrigin()) + _d);

    double t = vo / vd;
    if (t < 0) {
        return std::nullopt;
    }

    if (vd > 0) {
        _normal = -_normal;
    }

    glm::dvec3 point = {origin.x + dir.x * t, origin.y + dir.y * t, origin.z + dir.z * t};
    auto hit = std::make_unique<Rays::Hit>(t, point, _normal, this);
    return hit;
}
