//
// Created by Dallin Hagman on 9/21/21.
//

#ifndef CS655_PLANE_H
#define CS655_PLANE_H

#include "BaseRenderable.h"

class Plane: public BaseRenderable {
protected:
    glm::dvec3 _u, _v, _normal;
    double _d;
public:
    Plane(const std::unique_ptr<Material>& material, glm::dvec3 u, glm::dvec3 v);

    std::optional<std::unique_ptr<Rays::Hit>> intersect(const Rays::Ray *ray) override;
};


#endif //CS655_PLANE_H
