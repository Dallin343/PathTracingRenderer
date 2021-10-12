//
// Created by Dallin Hagman on 9/2/21.
//

#ifndef CS655_MATERIAL_H
#define CS655_MATERIAL_H

#include "Common.h"
#include "Texture.h"


enum MaterialType {
    Diffuse,
    Transparent,
    Textured
};

class Material {
private:
    MaterialType _type{};
    double _diffuseFac{}, _specularFac{}, _reflectiveFac{}, _glossyFac{}, _transmissionFac{}, _translucencyFac{};
    double _phongConst{}, _ior{};
    glm::dvec3 _diffuseColor{}, _specularColor{};

    const Texture* _texture;
public:
    Material();

    Material(double diffuseFac, double specularFac, double reflectiveFac, double glossy, double phongConst,
             const glm::dvec3 &diffuseColor, const glm::dvec3 &specularColor);

    Material(double reflectiveFac, double glossy, double transmissionFac, double translucency, double ior);

    Material(const Texture* texture);

    Material(const Texture* texture, double diffuseFac, double specularFac, double reflectiveFac, double glossy,
             double phongConst, const glm::dvec3 &specularColor);

    double getDiffuseFac() const;

    double getReflectiveFac() const;

    double getTransmissionFac() const;

    double getPhongConst() const;

    const glm::dvec3 &getDiffuseColor() const;

    const glm::dvec3 &getSpecularColor() const;

    double getSpecularFac() const;

    double getGlossyFac() const;

    double getTranslucencyFac() const;

    double getIor() const;

    MaterialType getType() const;

    const Texture *getTexture() const;
};


#endif //CS655_MATERIAL_H
