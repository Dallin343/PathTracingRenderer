//
// Created by Dallin Hagman on 9/2/21.
//

#include <algorithm>
#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(const glm::dvec3 &position, const glm::dvec3 &color) : Light(position, color) {}

glm::dvec3
DirectionalLight::calculateDiffuse(const Rays::Ray *ray, const Rays::Hit *hit, const Material *material,
                                   const std::vector<std::unique_ptr<BaseRenderable>> &objects) {

    auto nrm = hit->getNorm();

    double angle = glm::max(glm::dot(nrm, _position), 0.0);
    return material->getDiffuseFac() * material->getDiffuseColor() * angle * _color;
}

glm::dvec3
DirectionalLight::calculateSpecular(const Rays::Ray *ray, const Rays::Hit *hit, const Material *material,
                                    const std::vector<std::unique_ptr<BaseRenderable>> &objects,
                                    const Camera *camera) {

    auto nrm = hit->getNorm();
    glm::dvec3 reflection = glm::normalize(_position - 2.0 * nrm * glm::dot(nrm, _position));

    glm::dvec3 view = camera->getLookFrom() - hit->getPoint();
    double angle = glm::max(glm::dot(ray->getDirection(), reflection), 0.0);
    return material->getSpecularColor() * material->getSpecularFac() * glm::pow(angle, 4) *
           _color;
}

bool DirectionalLight::inShadow(const Rays::Ray *ray, const Rays::Hit *hit,
                                const std::vector<std::unique_ptr<BaseRenderable>> &objects) {
    auto adjOrigin = hit->getPoint() + _position * 0.0001;
    auto shadowRay = std::make_unique<Rays::IlluminationRay>(adjOrigin, _position);
    return Light::inShadow(shadowRay.get(), hit, objects);
}

double DirectionalLight::_intensity(const Rays::Ray *) {
    return 1.0;
}
