//
// Created by Dallin Hagman on 9/14/21.
//

#include <algorithm>
#include "Polygon.h"

Polygon::Polygon(const std::unique_ptr<Material> &material, std::vector<glm::dvec3> vertices) :
        Plane(material, vertices.at(0), vertices.at(1)), _vertices(std::move(vertices)), _projVertices({}) {

    _projVertices.resize(_vertices.size());
    auto absNormal = glm::abs(_normal);

    auto transform = [&](glm::dvec3 &v) {
        if (absNormal.x > absNormal.y && absNormal.x > absNormal.z) {
            return glm::dvec2(v.y, v.z);
        } else if (absNormal.y > absNormal.x && absNormal.y > absNormal.z) {
            return glm::dvec2(v.x, v.z);
        } else {
            return glm::dvec2(v.x, v.y);
        }
    };

    std::transform(_vertices.begin(), _vertices.end(), std::back_inserter(_projVertices), transform);
}

std::optional<std::unique_ptr<Rays::Hit>> Polygon::intersect(const Rays::Ray *ray) {
    //Refactor into Plane -> Polygon
    auto hit = Plane::intersect(ray);
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

    std::vector<glm::dvec2> transPoints;
    std::transform(_projVertices.begin(), _projVertices.end(), std::back_inserter(transPoints),
                   [&](glm::dvec2 point) {
                       return point - projHit;
                   }
    );

    int signHolder = transPoints.at(0).y < 0.0 ? -1 : 1;
    int nextSignHolder;
    int numCrossings = 0;
    for (unsigned int i = 0; i <= transPoints.size(); i++) {
        unsigned int nextI = i == transPoints.size() ? 0 : i + 1;
        auto curr = transPoints.at(i);
        auto next = transPoints.at(nextI);

        nextSignHolder = next.y < 0.0 ? -1 : 1;
        if (signHolder != nextSignHolder) {
            if (curr.x > 0.0 && next.x > 0.0) numCrossings++;
            else if (curr.x > 0.0 || next.x > 0.0) {
                auto uCross = curr.x - curr.y * ((next.x - curr.x)/(next.y - curr.y));
                if (uCross > 0.0) numCrossings++;
            }
        }
        signHolder = nextSignHolder;
    }

    if (numCrossings % 2 == 1) {
        auto hitValue = std::move(hit.value());
        hitValue->setObject(this);
        return hitValue;
    }

    return std::nullopt;
}