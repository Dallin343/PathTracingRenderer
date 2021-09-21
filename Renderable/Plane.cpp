//
// Created by Dallin Hagman on 9/21/21.
//

#include "Plane.h"

Plane::Plane(const std::unique_ptr<Material> &material, glm::dvec3 u, glm::dvec3 v) : BaseRenderable(material), _u(u),
                                                                                      _v(v) {
    _normal = glm::normalize(glm::cross(u, v));
    _d = glm::dot(u, _normal);
}

std::optional<std::unique_ptr<Rays::Hit>> Plane::intersect(const Rays::Ray *ray) {
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
