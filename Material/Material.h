//
// Created by Dallin Hagman on 9/2/21.
//

#ifndef CS655_MATERIAL_H
#define CS655_MATERIAL_H

#include <glm.hpp>

enum MaterialType {
    Diffuse,
    Transparent
};

class Material {
private:
    MaterialType _type{};
    double _diffuseFac{}, _specularFac{}, _reflectiveFac{}, _transmissionFac{}, _phongConst{}, _ior{};
    glm::dvec3 _diffuseColor{}, _specularColor{};
public:
    Material();

    Material(double diffuseFac, double specularFac, double reflectiveFac, double phongConst,
             const glm::dvec3 &diffuseColor, const glm::dvec3 &specularColor);

    Material(double reflectiveFac, double transmissionFac, double ior);

    double getDiffuseFac() const;

    double getReflectiveFac() const;

    double getTransmissionFac() const;

    double getPhongConst() const;

    const glm::dvec3 &getDiffuseColor() const;

    const glm::dvec3 &getSpecularColor() const;

    double getSpecularFac() const;

    double getIor() const;

    MaterialType getType() const;
};


#endif //CS655_MATERIAL_H
