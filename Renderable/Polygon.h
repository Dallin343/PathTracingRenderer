//
// Created by Dallin Hagman on 9/14/21.
//

#ifndef CS655_POLYGON_H
#define CS655_POLYGON_H


#include <vector>
#include "Plane.h"

class Polygon: public Plane {
private:
    std::vector<glm::dvec3> _vertices;
    std::vector<glm::dvec2> _projVertices;
public:
    Polygon(const std::unique_ptr<Material>& material, std::vector<glm::dvec3> vertices);
    std::optional<std::unique_ptr<Rays::Hit>> intersect(const Rays::Ray* ray) override;

};


#endif //CS655_POLYGON_H
