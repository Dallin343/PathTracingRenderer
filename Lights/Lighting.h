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

class Lighting {
public:
    static bool inShadow(const Rays::Ray*, const Light*, const std::vector<std::unique_ptr<BaseRenderable>> &);
    static glm::dvec3 calculateIllumination(const Rays::Ray*, const Rays::Hit*, const Light*, const Material*, const SceneDescription*);
    static glm::dvec3 calculateIllumination(const Rays::Ray*, const Rays::Hit*, const AreaLight*, const Material*, const SceneDescription*);

private:
    static glm::dvec3 _calculateIllumation(const Rays::Ray*, const Rays::Hit*, const Light*, const glm::dvec3&, const Material*, const Camera*);
    // static double _calculateShadowFactor(const Rays::Ray*, const Light*, const std::vector<std::unique_ptr<BaseRenderable>> &);
    // static double _calculateShadowFactor(const Rays::Ray*, const AreaLight*, const std::vector<std::unique_ptr<BaseRenderable>> &);
}
