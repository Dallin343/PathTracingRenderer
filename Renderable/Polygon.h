//
// Created by Dallin Hagman on 9/14/21.
//

#ifndef CS655_POLYGON_H
#define CS655_POLYGON_H


#include <vector>
#include "BaseRenderable.h"

class Polygon: public BaseRenderable {
private:
    std::vector<glm::dvec3> _vertices;
    std::vector<glm::dvec2> _projVertices;
    glm::dvec3 _normal;
    double _d;
public:
    Polygon(const std::unique_ptr<Material>& material, std::vector<glm::dvec3> vertices);

private:
    std::optional<std::unique_ptr<Rays::Hit>> planeIntersect(const Rays::Ray* ray);
    std::optional<std::unique_ptr<Rays::Hit>> intersect(const Rays::Ray* ray) override;

    const Material* getMaterial() override;
};


#endif //CS655_POLYGON_H
