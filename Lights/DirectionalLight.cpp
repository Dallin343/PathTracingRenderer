//
// Created by Dallin Hagman on 9/2/21.
//

#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(const glm::dvec3 &position, const glm::dvec3 &color) : Light(position, color) {}

glm::dvec3
DirectionalLight::calculateDiffuse(const std::shared_ptr<Rays::Ray> &ray, const std::shared_ptr<Rays::Hit> &hit,
                                   const std::shared_ptr<Material> &material,
                                   const std::shared_ptr<SceneDescription> &scene) {
    if (_inShadow(std::make_unique<Rays::IlluminationRay>(hit->getPoint(), _position), scene->getObjects())) {
        return { 0.0, 0.0, 0.0};
    }

    auto nrm = hit->getNorm();
    glm::dvec3 reflection = glm::normalize(2.0 * nrm * glm::dot(nrm, _position) - _position);

    double angle = glm::abs(glm::dot(nrm, _position));
    return material->getDiffuseFac() * material->getDiffuseColor() * angle * _color;
}

glm::dvec3
DirectionalLight::calculateSpecular(const std::shared_ptr<Rays::Ray> &ray, const std::shared_ptr<Rays::Hit> &hit,
                                    const std::shared_ptr<Material> &material,
                                    const std::shared_ptr<SceneDescription> &scene) {
    if (_inShadow(std::make_unique<Rays::IlluminationRay>(hit->getPoint(), _position), scene->getObjects())) {
        return { 0.0, 0.0, 0.0};
    }

    auto nrm = hit->getNorm();
    glm::dvec3 reflection = glm::normalize(2.0 * nrm * glm::dot(nrm, _position) - _position);

    glm::dvec3 view = scene->getCamera()->getLookFrom() - hit->getPoint();
    double angle = glm::abs(glm::dot(ray->getDirection(), reflection));
//    return material->getSpecularColor() * glm::pow(angle, material->getGloss()) * _color;
    return {0.0, 0.0, 0.0};
}
