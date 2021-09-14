//
// Created by Dallin Hagman on 9/14/21.
//

#ifndef CS655_TRIANGLE_H
#define CS655_TRIANGLE_H


#include "BaseRenderable.h"

class Triangle: public BaseRenderable {
private:
    glm::dvec3 _p1;
    glm::dvec3 _p2;
    glm::dvec3 _p3;
public:
    Triangle(const std::unique_ptr<Material>& material, glm::dvec3 p1, glm::dvec3 p2, glm::dvec3 p3);

private:
    std::optional<std::unique_ptr<Rays::Hit>> Intersect(const Rays::Ray* ray) override;

    const Material* GetMaterial() override;
};


#endif //CS655_TRIANGLE_H
