//
// Created by dallin on 9/14/21.
//

#include "PointLight.h"

glm::dvec3 PointLight::calculateDiffuse(const Rays::Ray *ray, const Rays::Hit *hit, const Material *material,
                                        const std::vector<std::unique_ptr<BaseRenderable>> &objects) {
    glm::dvec3 dirToLight = glm::normalize(_position - hit->getPoint());

    auto nrm = hit->getNorm();

    double angle = glm::max(glm::dot(nrm, dirToLight), 0.0);
    return material->getDiffuseFac() * material->getDiffuseColor() * angle * _color * _intensity(ray);
}

glm::dvec3 PointLight::calculateSpecular(const Rays::Ray *ray, const Rays::Hit *hit, const Material *material,
                                         const std::vector<std::unique_ptr<BaseRenderable>> &objects,
                                         const Camera *camera) {
    glm::dvec3 dirToLight = glm::normalize(_position - hit->getPoint());

    auto nrm = hit->getNorm();
    glm::dvec3 reflection = glm::normalize(dirToLight - 2.0 * nrm * glm::dot(nrm, dirToLight));

    glm::dvec3 view = camera->getLookFrom() - hit->getPoint();
    double angle = glm::max(glm::dot(ray->getDirection(), reflection), 0.0);
    return material->getSpecularColor() * material->getSpecularFac() * glm::pow(angle, 4) *
           _color * _intensity(ray);
}

PointLight::PointLight(const glm::dvec3 &position, const glm::dvec3 &color) : Light(position, color) {}

bool PointLight::inShadow(const Rays::Ray *ray, const Rays::Hit *hit,
                          const std::vector<std::unique_ptr<BaseRenderable>> &objects) {
    glm::dvec3 dirToLight = glm::normalize(_position - hit->getPoint());
    auto adjOrigin = hit->getPoint() + dirToLight * 0.0001;
    auto shadowRay = std::make_unique<Rays::IlluminationRay>(adjOrigin, dirToLight);
    return Light::inShadow(shadowRay.get(), hit, objects);
}

double PointLight::_intensity(const Rays::Ray *ray) {
    double d = glm::distance(_position, ray->getOrigin());
    return 1000.0 / (4 * M_PI * d*d);
}
