//
// Created by Dallin Hagman on 9/2/21.
//

#ifndef CS655_SPHERE_H
#define CS655_SPHERE_H

#include "BaseRenderable.h"

class Sphere: public BaseRenderable {
private:
    glm::dvec3 _origin;
    double _radius;
public:
    Sphere(const std::unique_ptr<Material>& material, glm::dvec3 origin, double radius);

private:
    std::optional<std::unique_ptr<Rays::Hit>> Intersect(const Rays::Ray* ray) override;

    const Material* GetMaterial() override;
};


#endif //CS655_SPHERE_H
