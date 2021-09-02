//
// Created by Dallin Hagman on 9/2/21.
//

#include "Material.h"

Material::Material(double diffuseFac, double specularFac, double ambientFac, const glm::dvec3 &diffuseColor,
                   const glm::dvec3 &specularColor, double gloss) : diffuse_fac(diffuseFac),
                                                                         specular_fac(specularFac),
                                                                         ambient_fac(ambientFac),
                                                                         diffuse_color(diffuseColor),
                                                                         specular_color(specularColor), gloss(gloss) {}

Material::Material() : diffuse_fac(1.0), specular_fac(1.0), ambient_fac(0.2), diffuse_color(1.0, 0.0, 0.0),
                       specular_color(1.0, 1.0, 1.0), gloss(2.0) {}
