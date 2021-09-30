#include "Lighting.h"

#include "Material/Material.h"

namespace Lighting {
    bool inShadow(const Rays::Ray *ray, const Light *light, const std::vector<std::unique_ptr<BaseRenderable>> &objects) {
        for (const auto& object : objects) {
            auto hit = object->intersect(ray);
            if (hit.has_value() && hit.value()->getObject()->getMaterial()->getType() != Transparent) {
                return true;
            }
        }
        return false;
    }

    glm::dvec3 calculateIllumination(const Rays::Ray* ray, const Rays::Hit* hit, const Light* light, const Material* material, const SceneDescription* scene) {
        return _calculateIllumination(ray, hit, light, light->getPosition(), material, scene->getCamera());
    }

    glm::dvec3 calculateIllumination(const Rays::Ray* ray, const Rays::Hit* hit, const AreaLight* light, const Material* material, const SceneDescription* scene) {
        glm::dvec3 color;
        int numShadows = 0;
        std::vector<glm::dvec3> samples = light->getSamplePositions();
        auto lightRay = std::make_unique<Rays::IlluminationRay>();
        for (const auto& sample : samples) {
            glm::dvec3 dir = glm::normalize(sample - hit->getPoint());
            lightRay->setOrigin(hit->getPoint() + dir*BIAS);
            lightRay->setDirection(dir);

            if (inShadow(lightRay.get(), light, scene->getObjects())) {
                numShadows++;
            } else {
                color += _calculateIllumination(ray, hit, light, sample, material, scene->getCamera());
            }
        }

        color *= (1.0 - ((double)numShadows / samples.size()));
        return color;
    }

    glm::dvec3 _calculateIllumination(const Rays::Ray* ray, const Rays::Hit* hit, const Light* light, const glm::dvec3& position, const Material* material, const Camera* camera) {
        //Diffuse
        glm::dvec3 diffuse, specular;

        glm::dvec3 nrm = hit->getNorm();

        glm::dvec3 color = light->getColor() * light->attenuate(hit->getPoint(), position);

        double angle = glm::max(glm::dot(nrm, position), 0.0);
        diffuse = material->getDiffuseFac() * material->getDiffuseColor() * angle * color;

        //Specular
        glm::dvec3 reflection = glm::normalize(position - 2.0 * nrm * glm::dot(nrm, position));

        glm::dvec3 view = camera->getLookFrom() - hit->getPoint();
        double angle = glm::max(glm::dot(ray->getDirection(), reflection), 0.0);
        specular = material->getSpecularColor() * material->getSpecularFac() * glm::pow(angle, 4) * color;
    }
}
