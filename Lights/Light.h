//
// Created by Dallin Hagman on 9/2/21.
//

#ifndef CS655_LIGHT_H
#define CS655_LIGHT_H

#include "Common.h"

#include "Renderable/BaseRenderable.h"
#include "Rays/Ray.h"
#include "Material/Material.h"
#include "Scene/Camera.h"
#include "Rays/Hit.h"

enum Type {
    Base, Directional, Point, Area
};

class Light {
protected:
    glm::dvec3 _position;
    glm::dvec3 _color;
    double _intensity;

public:
    Light(const glm::dvec3 &position, const glm::dvec3 &color, double intensity);

    const glm::dvec3 &getPosition() const;

    void setPosition(const glm::dvec3 &position);

    const glm::dvec3 &getColor() const;

    void setColor(const glm::dvec3 &color);

    virtual double attenuate(const glm::dvec3&, const glm::dvec3&) const;

    virtual std::vector<glm::dvec3> getSamplePositions() const;

    virtual Type getType() const { return Type::Base; }
};


#endif //CS655_LIGHT_H
