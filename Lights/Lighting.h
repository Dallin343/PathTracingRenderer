#pragma once

#include "Common.h"

#include "Renderable/BaseRenderable.h"
#include "Scene/SceneDescription.h"

#include "Light.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "AreaLight.h"

#include "Rays/Ray.h"
#include "Rays/Hit.h"

namespace Lighting {
    bool inShadow(const Rays::Ray*, const Light*, const std::vector<std::unique_ptr<BaseRenderable>> &);
    
    glm::dvec3 calculateIllumination(const Rays::Ray*, const Rays::Hit*, const Material*, const SceneDescription*);
    glm::dvec3 calculateIllumination(const Rays::Ray*, const Rays::Hit*, const Light*, const Material*, const SceneDescription*);
    glm::dvec3 calculateIllumination(const Rays::Ray*, const Rays::Hit*, const AreaLight*, const Material*, const SceneDescription*);


    std::unique_ptr<Rays::ReflectionRay> reflect(const Rays::Ray *, const Rays::Hit *);
    std::unique_ptr<Rays::TransmissionRay> refract(const Rays::Ray *, const Rays::Hit *);
    double fresnel(const Rays::Ray *, const Rays::Hit *);

    std::unique_ptr<Rays::ReflectionRay> randomDiffuse(const Rays::Ray *, const Rays::Hit *);
    std::unique_ptr<Rays::ReflectionRay> randomSpecular(const Rays::Ray *, const Rays::Hit *);
    std::unique_ptr<Rays::TransmissionRay> randomRefraction(const Rays::Ray *, const Rays::Hit *);
    glm::dvec3 _vectorInHemisphere(glm::dvec3 localX, glm::dvec3 localZ, double theta, double phi);


    glm::dvec3 _calculateIllumination(const Rays::Ray*, const Rays::Hit*, const Light*, const glm::dvec3&, const Material*, const Camera*);
};
