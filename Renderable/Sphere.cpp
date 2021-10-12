//
// Created by Dallin Hagman on 9/2/21.
//

#include "Sphere.h"
#include <glm.hpp>

glm::dvec2 Sphere::texCoords(const glm::dvec3 &norm)
{
    auto localNorm = norm * _cob;

    return {atan2(localNorm.z, localNorm.x) / (2 * M_PI) + 0.5, 0.5 - asin(localNorm.y) / M_PI};
}

std::optional<std::unique_ptr<Rays::Hit>> Sphere::intersect(const Rays::Ray *ray)
{
    PROFILE_FUNCTION();
    glm::dvec3 oc = _origin - ray->getOrigin();
    double tca = glm::dot(oc, ray->getDirection());

    bool outside = glm::length(oc) > _radius;

    if (tca < 0.0 && outside) {
        return std::nullopt;
    }

    double d2 = glm::dot(oc, oc) - (tca * tca);

    if (d2 > _radius * _radius) {
        return std::nullopt;
    }

    double thc2 = _radius * _radius - d2;
    if (thc2 < 0.0) {
        return std::nullopt;
    }

    double thc = glm::sqrt(thc2);
    double t0 = tca - thc;
    double t1 = tca + thc;

    if (t0 <= 0.0 && t1 <= 0.0) {
        return std::nullopt;
    }

    double t;
    if (t0 < 0.0) {
        t = t1;
    } else if (t1 < 0.0) {
        t = t0;
    } else {
        t = t0 < t1 ? t0 : t1;
    }

    glm::dvec3 point = ray->getOrigin() + (ray->getDirection() * t);
    glm::dvec3 norm = glm::normalize((point - _origin));
    glm::dvec2 uv = texCoords(norm);
    return std::make_unique<Rays::Hit>(t, point, norm, uv, this);
}

Sphere::Sphere(const std::unique_ptr<Material> &material, glm::dvec3 origin, double radius) : BaseRenderable(
        material), _origin(origin), _radius(radius)
{
    _bounds.min = _origin - _radius;
    _bounds.max = _origin + _radius;
}

Sphere::Sphere(const std::unique_ptr<Material> &material, glm::dvec3 origin, double radius, glm::dvec3 up,
               glm::dvec3 right) : BaseRenderable(material), _origin(origin), _radius(radius), _up(up), _right(right)
{
    _bounds.min = _origin - _radius;
    _bounds.max = _origin + _radius;
    _in = glm::cross(up, right);

    glm::dmat3 localBasis = {_right, _up, _in};
    _cob = WORLD_BASIS * localBasis;
}
