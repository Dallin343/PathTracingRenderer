//
// Created by Dallin Hagman on 9/2/21.
//

#ifndef CS655_DIRECTIONALLIGHT_H
#define CS655_DIRECTIONALLIGHT_H

#include "Light.h"

class DirectionalLight: public Light {
public:
    DirectionalLight(const glm::dvec3 &position, const glm::dvec3 &color);

    glm::dvec3 calculateDiffuse(const std::shared_ptr<Rays::Ray> &, const std::shared_ptr<Rays::Hit> &,
                                const std::shared_ptr<Material> &, const std::shared_ptr<SceneDescription>&) override;

    glm::dvec3 calculateSpecular(const std::shared_ptr<Rays::Ray> &, const std::shared_ptr<Rays::Hit> &,
                                 const std::shared_ptr<Material> &, const std::shared_ptr<SceneDescription>&) override;
};


#endif //CS655_DIRECTIONALLIGHT_H
