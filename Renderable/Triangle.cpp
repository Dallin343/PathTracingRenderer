//
// Created by Dallin Hagman on 9/14/21.
//

#include "Triangle.h"

Triangle::Triangle(const std::unique_ptr<Material> &material, glm::dvec3 p1, glm::dvec3 p2, glm::dvec3 p3)
        : BaseRenderable(material), _p1(p1), _p2(p2), _p3(p3) {

}

std::optional<std::unique_ptr<Rays::Hit>> Triangle::Intersect(const Rays::Ray *ray) {
    return std::optional<std::unique_ptr<Rays::Hit>>();
}

const Material *Triangle::GetMaterial() {
    return nullptr;
}
