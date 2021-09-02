//
// Created by Dallin Hagman on 9/2/21.
//

#ifndef CS655_LIGHT_H
#define CS655_LIGHT_H

#include <glm/vec3.hpp>

class Light {
private:
    glm::dvec3 _position;
    glm::dvec3 _color;
public:
    Light(const glm::dvec3 &position, const glm::dvec3 &color);

    const glm::dvec3 &getPosition() const;

    void setPosition(const glm::dvec3 &position);

    const glm::dvec3 &getColor() const;

    void setColor(const glm::dvec3 &color);
};


#endif //CS655_LIGHT_H
