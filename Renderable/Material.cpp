#include "Material.h"

Material::Material() : _diffuseFac(0.6), _reflectiveFac(0.1), _specularFac(0.2), _transmissionFac(1.0), _phongConst(0.5),
                       _diffuseColor({1.0, 0.0, 0.0}),
                       _specularColor(1.0, 1.0, 1.0) {}

Material::Material(double diffuseFac, double reflectiveFac, double specularFac, double transmissionFac,
                   double phongConst, const glm::dvec3 &diffuseColor,
                   const glm::dvec3 &specularColor) : _diffuseFac(diffuseFac), _reflectiveFac(reflectiveFac),
                                                      _specularFac(specularFac),
                                                      _transmissionFac(transmissionFac),
                                                      _phongConst(phongConst), _diffuseColor(diffuseColor),
                                                      _specularColor(specularColor) {}

double Material::getDiffuseFac() const {
    return _diffuseFac;
}

double Material::getTransmissionFac() const {
    return _transmissionFac;
}

double Material::getPhongConst() const {
    return _phongConst;
}

const glm::dvec3 &Material::getDiffuseColor() const {
    return _diffuseColor;
}

const glm::dvec3 &Material::getSpecularColor() const {
    return _specularColor;
}

double Material::getSpecularFac() const {
    return _specularFac;
}

double Material::getReflectiveFac() const {
    return _reflectiveFac;
}

