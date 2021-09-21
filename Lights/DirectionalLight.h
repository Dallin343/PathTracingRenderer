//
// Created by Dallin Hagman on 9/2/21.
//

#ifndef CS655_DIRECTIONALLIGHT_H
#define CS655_DIRECTIONALLIGHT_H

#include "Light.h"

class DirectionalLight : public Light {
protected:
    virtual double _intensity(const Rays::Ray *);
public:
    DirectionalLight(const glm::dvec3 &position, const glm::dvec3 &color);

    glm::dvec3 calculateDiffuse(const Rays::Ray *, const Rays::Hit *, const Material *,
                                const std::vector<std::unique_ptr<BaseRenderable>> &) override;

    glm::dvec3 calculateSpecular(const Rays::Ray *, const Rays::Hit *, const Material *,
                                 const std::vector<std::unique_ptr<BaseRenderable>> &,
                                 const Camera *) override;

    bool inShadow(const Rays::Ray *ray, const Rays::Hit *hit,
                  const std::vector<std::unique_ptr<BaseRenderable>> &vector) override;
};


#endif //CS655_DIRECTIONALLIGHT_H
