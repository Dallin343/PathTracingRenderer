//
// Created by Dallin Hagman on 9/2/21.
//

#include "Sphere.h"
#include <glm.hpp>

std::optional<std::shared_ptr<Rays::Hit>> Sphere::Intersect(std::shared_ptr<Rays::Ray> ray) {
    glm::dvec3 oc = _origin - ray.getOrigin();
    double adj = glm::dot(oc, ray.getDirection());

    if (adj < 0.0) {
        return std::nullopt;
    }

    double d2 = glm::dot(oc, oc) - (adj * adj);

    if (d2 > _radius * _radius) {
        return std::nullopt;
    }

    double thc = glm::sqrt(_radius * _radius - d2);
    double t0 = adj - thc;
    double t1 = adj + thc;

    if (t0 <= 0.0 && t1 <= 0.0) {
        return std::nullopt;
    }

    double t = t0 < t1 ? t0 : t1;

    glm::dvec3 point = ray.getOrigin() + (ray.getDirection() * t);
    glm::dvec3 norm = (point - _origin) / _radius;

    return std::make_shared<Rays::Hit>(t, point, norm);
}

std::shared_ptr<Material> Sphere::GetMaterial() {
    return _material;
}

Sphere::Sphere(std::shared_ptr<Material> material, glm::dvec3 origin, double radius) : BaseRenderable(material), _origin(origin),
                                                                            _radius(radius) {}
