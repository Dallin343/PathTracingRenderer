//
// Created by Dallin Hagman on 9/2/21.
//

#ifndef CS655_MATERIAL_H
#define CS655_MATERIAL_H

#include "Common.h"

class Material {
private:
    double diffuse_fac, specular_fac, ambient_fac;
    glm::dvec3 diffuse_color, specular_color;
    double gloss;
public:
    Material();

    Material(double diffuseFac, double specularFac, double ambientFac, const glm::dvec3 &diffuseColor,
             const glm::dvec3 &specularColor, double gloss);
};


#endif //CS655_MATERIAL_H
