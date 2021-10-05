#include "Material.h"

Material::Material() = default;

Material::Material(double diffuseFac, double specularFac, double reflectiveFac, double glossy, double phongConst,
                   const glm::dvec3 &diffuseColor,
                   const glm::dvec3 &specularColor) : _type(Diffuse), _diffuseFac(diffuseFac),
                                                      _specularFac(specularFac),
                                                      _reflectiveFac(reflectiveFac),
                                                      _glossyFac(glossy),
                                                      _phongConst(phongConst),
                                                      _diffuseColor(diffuseColor),
                                                      _specularColor(specularColor) {}

Material::Material(double reflectiveFac, double glossy, double transmissionFac, double translucency, double ior)
        : _type(Transparent),
          _reflectiveFac(reflectiveFac),
          _glossyFac(glossy),
          _translucencyFac(translucency),
          _transmissionFac(transmissionFac), _ior(ior) {

}

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

double Material::getIor() const {
    return _ior;
}

double Material::getReflectiveFac() const {
    return _reflectiveFac;
}

MaterialType Material::getType() const {
    return _type;
}

double Material::getGlossyFac() const {
    return _glossyFac;
}

double Material::getTranslucencyFac() const {
    return _translucencyFac;
}


