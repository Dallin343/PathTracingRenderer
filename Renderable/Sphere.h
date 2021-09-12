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
    Sphere(std::shared_ptr<Material> material, glm::dvec3 origin, double radius);

private:
    std::optional<std::shared_ptr<Rays::Hit>> Intersect(std::shared_ptr<Rays::Ray> ray) override;

    std::shared_ptr<Material> GetMaterial() override;
};


#endif //CS655_SPHERE_H
