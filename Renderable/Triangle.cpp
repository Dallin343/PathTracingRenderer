//
// Created by Dallin Hagman on 9/14/21.
//

#include "Triangle.h"

Triangle::Triangle(const std::unique_ptr<Material> &material, glm::dvec3 p1, glm::dvec3 p2, glm::dvec3 p3)
        : BaseRenderable(material), _p1(p1), _p2(p2), _p3(p3) {

    _bounds.min = {std::min({_p1.x, _p2.x, _p3.x}), std::min({_p1.y, _p2.y, _p3.y}),std::min({_p1.z, _p2.z, _p3.z})};
    _bounds.max = {std::max({_p1.x, _p2.x, _p3.x}), std::max({_p1.y, _p2.y, _p3.y}),std::max({_p1.z, _p2.z, _p3.z})}
}

std::optional<std::unique_ptr<Rays::Hit>> Triangle::intersect(const Rays::Ray *ray) {
    double e = 0.000001;
    glm::dvec3 w0 = ray->getOrigin() - _p2;
    double num = -(glm::dot(_calcNormal(), w0));
    double den = glm::dot(_calcNormal(), ray->getDirection());

    if (glm::abs(den) < e) {
        return std::nullopt;
    }

    double intersect_dist = num / den;

    if (intersect_dist >= 0.0) {
        glm::dvec3 point = ray->getOrigin() + ray->getDirection() * intersect_dist;
        glm::dvec3 u = _p1 - _p2;
        glm::dvec3 v = _p3 - _p2;

        double uu = glm::dot(u, u);
        double uv = glm::dot(u, v);
        double vv = glm::dot(v, v);
        auto w = point - _p2;
        double wu = glm::dot(w, u);
        double wv = glm::dot(w, v);
        den = (uv * uv) - (uu * vv);

        double s = ((uv * wv) - (vv * wu)) / den;

        if (s < 0.0 || s > 1.0) {
            return std::nullopt;
        }

        double t = ((uv * wu) - (uu * wv)) / den;
        if (t < 0.0 || (s+t) > 1.0) {
            return std::nullopt;
        }

        auto norm = _calcNormal();
        auto hit = std::make_unique<Rays::Hit>(t, point, norm, this);
        return hit;
    }
    return std::nullopt;
}

glm::dvec3 Triangle::_calcNormal() {
    glm::dvec3 v1 = _p1 - _p2;
    glm::dvec3 v2 = _p3 - _p2;
    return glm::normalize(glm::cross(v2, v1));
}
