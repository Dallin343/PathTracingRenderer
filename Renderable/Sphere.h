//
// Created by Dallin Hagman on 9/2/21.
//

#ifndef CS655_SPHERE_H
#define CS655_SPHERE_H

#include "BaseRenderable.h"

class Sphere : public BaseRenderable
{
private:
    glm::dvec3 _origin;
    double _radius;

    glm::dvec3 _up{0.0, 1.0, 0.0}, _right{1.0, 0.0, 0.0}, _in{0.0, 0.0, -1.0};
    glm::dmat3 _cob{};
public:
    Sphere(const std::unique_ptr<Material> &material, glm::dvec3 origin, double radius);

    Sphere(const std::unique_ptr<Material> &material, glm::dvec3 origin, double radius, glm::dvec3 up,
           glm::dvec3 right);

    std::optional<std::unique_ptr<Rays::Hit>> intersect(const Rays::Ray *ray) override;

private:
    glm::dvec2 texCoords(const glm::dvec3 &norm);
};


#endif //CS655_SPHERE_H
