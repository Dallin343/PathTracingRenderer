//
// Created by Dallin Hagman on 9/2/21.
//

#ifndef CS655_DIRECTIONALLIGHT_H
#define CS655_DIRECTIONALLIGHT_H

#include "Light.h"

class DirectionalLight : public Light {
protected:
    bool _inShadow(const Rays::IlluminationRay *,
                   const std::vector<std::unique_ptr<BaseRenderable>> &) override;

public:
    DirectionalLight(const glm::dvec3 &position, const glm::dvec3 &color);

    glm::dvec3 calculateDiffuse(const Rays::Ray *, const Rays::Hit *, const Material *,
                                const std::vector<std::unique_ptr<BaseRenderable>> &) override;

    glm::dvec3 calculateSpecular(const Rays::Ray *, const Rays::Hit *, const Material *,
                                 const std::vector<std::unique_ptr<BaseRenderable>> &,
                                 const Camera *) override;
};


#endif //CS655_DIRECTIONALLIGHT_H
