#include "Lighting.h"

#include "Material/Material.h"

namespace Lighting {
    void createCoordinateSystem(const glm::dvec3 &N, glm::dvec3 &Nt, glm::dvec3 &Nb)
    {
        if (std::fabs(N.x) > std::fabs(N.y))
            Nt = glm::dvec3(N.z, 0, -N.x) / glm::sqrt(N.x * N.x + N.z * N.z);
        else
            Nt = glm::dvec3(0, -N.z, N.y) / glm::sqrt(N.y * N.y + N.z * N.z);
        Nb = glm::cross(N, Nt);
    }

    glm::dvec3 uniformSampleHemisphere(const float &r1, const float &r2)
    {
        double sinTheta = sqrtf(1 - r1 * r1);
        double phi = 2.0 * M_PI * r2;
        double x = sinTheta * cos(phi);
        double z = sinTheta * sin(phi);
        return {x, r1, z};
    }

    bool
    inShadow(const Rays::Ray *ray, const Light *light, const std::vector<std::unique_ptr<BaseRenderable>> &objects) {
        for (const auto &object: objects) {
            auto hit = object->intersect(ray);
            if (hit.has_value() && hit.value()->getObject()->getMaterial()->getType() != Transparent) {
                return true;
            }
        }
        return false;
    }

    glm::dvec3 calculateIllumination(const Rays::Ray *ray, const Rays::Hit *hit, const Material *material,
                                     const SceneDescription *scene) {
        glm::dvec3 illumination = {};
        for (const auto &light: scene->getLights()) {
            switch (light->getType()) {
                case Type::Area: {
                    illumination += calculateIllumination(ray, hit, (const AreaLight *)light.get(), material, scene);
                    break;
                }
                case Type::Base:
                case Type::Directional:
                case Type::Point: {
                    illumination += calculateIllumination(ray, hit, light.get(), material, scene);
                    break;
                }
            }
        }
        return illumination;
    }

    glm::dvec3
    calculateIllumination(const Rays::Ray *ray, const Rays::Hit *hit, const Light *light, const Material *material,
                          const SceneDescription *scene) {
        const glm::dvec3 &lightPos = light->getPosition();
        const glm::dvec3 dir = glm::normalize(lightPos - hit->getPoint());
        const glm::dvec3 adjOrigin = hit->getPoint() + hit->getNorm() * BIAS;
        auto shadowRay = std::make_unique<Rays::Ray>(adjOrigin, dir);
        if (!inShadow(shadowRay.get(), light, scene->getObjects())) {
            return _calculateIllumination(ray, hit, light, light->getPosition(), material, scene->getCamera());
        }
        return {};
    }

    glm::dvec3
    calculateIllumination(const Rays::Ray *ray, const Rays::Hit *hit, const AreaLight *light, const Material *material,
                          const SceneDescription *scene) {
        glm::dvec3 color;
        int numShadows = 0;
        std::vector<glm::dvec3> samples = light->getSamplePositions();
        auto lightRay = std::make_unique<Rays::IlluminationRay>();
        for (const auto &sample: samples) {
            glm::dvec3 dir = glm::normalize(sample - hit->getPoint());
            lightRay->setOrigin(hit->getPoint() + hit->getNorm() * BIAS);
            lightRay->setDirection(dir);

            if (inShadow(lightRay.get(), light, scene->getObjects())) {
                numShadows++;
            } else {
                color += _calculateIllumination(ray, hit, light, sample, material, scene->getCamera());
            }
        }
        color *= (1.0 - ((double) numShadows / (NUM_SHADOW_SAMPLES*NUM_SHADOW_SAMPLES)));
        return color;
    }

    glm::dvec3
    _calculateIllumination(const Rays::Ray *ray, const Rays::Hit *hit, const Light *light, const glm::dvec3 &position,
                           const Material *material, const Camera *camera) {
        //Diffuse
        glm::dvec3 diffuse, specular;

        glm::dvec3 nrm = hit->getNorm();

        glm::dvec3 color = light->getColor() * light->attenuate(hit->getPoint(), position);

        double angle;
        if (material->getType() == Textured) {
            auto uv = hit->getTexCoords();
            auto texture = material->getTexture();
            diffuse = texture->linear(uv) * material->getDiffuseFac();
        } else {
            angle = glm::max(glm::dot(nrm, position), 0.0);
            diffuse = material->getDiffuseFac() * material->getDiffuseColor() * angle * color;
        }

        //Specular
        glm::dvec3 reflection = glm::normalize(position - 2.0 * nrm * glm::dot(nrm, position));

        glm::dvec3 view = camera->getLookFrom() - hit->getPoint();
        angle = glm::max(glm::dot(ray->getDirection(), reflection), 0.0);
        specular = material->getSpecularColor() * material->getSpecularFac() * glm::pow(angle, 4) * color;

        return diffuse + specular;
    }

    std::unique_ptr<Rays::ReflectionRay> reflect(const Rays::Ray *ray, const Rays::Hit *hit) {
        double e = 0.00001;
        auto currentDir = ray->getDirection();
        auto norm = hit->getNorm();
        glm::dvec3 reflectionDir = glm::normalize(currentDir - norm * 2.0 * glm::dot(currentDir, norm));

        glm::dvec3 bias = glm::dot(currentDir, norm) < 0.0 ? norm * e : norm * -e;
        return std::make_unique<Rays::ReflectionRay>(hit->getPoint() + bias, reflectionDir);
    }

    std::unique_ptr<Rays::TransmissionRay> refract(const Rays::Ray *ray, const Rays::Hit *hit) {
        double e = 1e-8;
        glm::dvec3 I = ray->getDirection();
        glm::dvec3 N = hit->getNorm();
        double ior = hit->getObject()->getMaterial()->getIor();

        double cosi = glm::clamp(glm::dot(I, N), -1.0, 1.0);
        double n1 = 1.0, n2 = ior;
        glm::dvec3 n = N;
        if (cosi < 0) { cosi = -cosi; }
        else {
            std::swap(n1, n2);
            n = -N;
        }
        double eta = n1 / n2;
        double k = 1 - eta * eta * (1 - cosi * cosi);
        glm::dvec3 refractDir = k < 0.0 ? glm::dvec3() : eta * I + (eta * cosi - glm::sqrt(k)) * n;
        refractDir = glm::normalize(refractDir);

        bool outside = glm::dot(I, N) < 0;
        glm::dvec3 bias = e * N;
        glm::dvec3 origin = outside ? hit->getPoint() - bias : hit->getPoint() + bias;
        return std::make_unique<Rays::TransmissionRay>(origin, refractDir);
    }

    double fresnel(const Rays::Ray *ray, const Rays::Hit *hit) {
        glm::dvec3 I = ray->getDirection();
        glm::dvec3 N = hit->getNorm();
        double ior = hit->getObject()->getMaterial()->getIor();

        double cosi = glm::clamp(glm::dot(I, N), -1.0, 1.0);
        double etai = 1, etat = ior;
        if (cosi > 0) { std::swap(etai, etat); }
        // Compute sini using Snell's law
        double sint = etai / etat * glm::sqrt(glm::max(0.0, 1 - cosi * cosi));
        // Total internal reflection
        if (sint >= 1) {
            return 1;
        } else {
            double cost = glm::sqrt(glm::max(0.0, 1 - sint * sint));
            cosi = glm::abs(cosi);
            double Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
            double Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
            return (Rs * Rs + Rp * Rp) / 2.0;
        }
    }

    std::unique_ptr<Rays::ReflectionRay> randomDiffuse(const Rays::Ray *ray, const Rays::Hit *hit) {

        double theta = 2 * M_PI * Util::_random();
        double phi = glm::acos(glm::sqrt(Util::_random()));

        auto norm = hit->getNorm();
        auto origin = hit->getPoint();
        auto dir = ray->getDirection();

        auto proj = glm::normalize(dir - (glm::dot(norm, dir) / glm::pow(glm::length(norm), 2)) * norm);
        auto reflection = _vectorInHemisphere(proj, norm, theta, phi);
        return std::make_unique<Rays::ReflectionRay>(origin + reflection*BIAS, reflection);
    }


    std::unique_ptr<Rays::ReflectionRay> randomSpecular(const Rays::Ray *ray, const Rays::Hit *hit) {
        auto reflRay = reflect(ray, hit);
        double theta = 2 * M_PI * Util::_random();
        double phi = glm::acos(glm::sqrt(Util::_random() * 0.1));

        auto localZ = reflRay->getDirection();
        auto origin = hit->getPoint();
        auto dir = ray->getDirection();

        auto proj = glm::normalize(dir - (glm::dot(localZ, dir) / glm::pow(glm::length(localZ), 2)) * localZ);

        auto reflection = _vectorInHemisphere(proj, localZ, theta, phi);
        return std::make_unique<Rays::ReflectionRay>(origin, reflection);
    }

    std::unique_ptr<Rays::TransmissionRay> randomRefraction(const Rays::Ray *ray, const Rays::Hit *hit) {
        double e1 = Util::_random();
        double e2 = Util::_random();
        double theta = 2 * M_PI * e1;
        double phi = glm::acos(glm::sqrt(e2));

        return std::unique_ptr<Rays::TransmissionRay>();
    }

    glm::dvec3 _vectorInHemisphere(glm::dvec3 localX, glm::dvec3 localZ, double theta, double phi) {
        auto localY = glm::normalize(glm::cross(localX, localZ));

        glm::dvec3 azimuth = glm::cos(theta)*localX + glm::sin(theta)*localY;
        glm::dvec3 zenith = glm::cos(phi)*azimuth + glm::sin(phi)*localZ;
        return zenith;
    }
}
