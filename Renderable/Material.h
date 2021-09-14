//
// Created by Dallin Hagman on 9/2/21.
//

#ifndef CS655_MATERIAL_H
#define CS655_MATERIAL_H

#include <glm.hpp>

class Material {
private:
    double _diffuseFac, _specularFac, _transmissionFac, _phongConst;
    glm::dvec3 _diffuseColor, _specularColor;
public:
    Material();

    Material(double diffuseFac, double specularFac, double transmissionFac, double phongConst, const glm::dvec3 &diffuseColor,
             const glm::dvec3 &specularColor);

    double getDiffuseFac() const;

    double getTransmissionFac() const;

    double getPhongConst() const;

    const glm::dvec3 &getDiffuseColor() const;

    const glm::dvec3 &getSpecularColor() const;

    double getSpecularFac() const;
};


#endif //CS655_MATERIAL_H
