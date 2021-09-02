//
// Created by Dallin Hagman on 9/2/21.
//

#ifndef CS655_DIRECTIONALLIGHT_H
#define CS655_DIRECTIONALLIGHT_H

#include "Light.h"

class DirectionalLight: Light {
public:
    DirectionalLight(const glm::dvec3 &position, const glm::dvec3 &color);
};


#endif //CS655_DIRECTIONALLIGHT_H
