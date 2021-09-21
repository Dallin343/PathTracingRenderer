//
// Created by dallin on 9/14/21.
//

#ifndef CS655_POINTLIGHT_H
#define CS655_POINTLIGHT_H


#include "Light.h"

class PointLight: public Light {
protected:
    virtual double _intensity(const Rays::Ray *);
public:
    PointLight(const glm::dvec3 &position, const glm::dvec3 &color);

    glm::dvec3 calculateDiffuse(const Rays::Ray *ray, const Rays::Hit *hit, const Material *material,
                                const std::vector<std::unique_ptr<BaseRenderable>> &vector) override;

    glm::dvec3 calculateSpecular(const Rays::Ray *ray, const Rays::Hit *hit, const Material *material,
                                 const std::vector<std::unique_ptr<BaseRenderable>> &vector,
                                 const Camera *camera) override;

    bool inShadow(const Rays::Ray *ray, const Rays::Hit *hit,
                  const std::vector<std::unique_ptr<BaseRenderable>> &vector) override;
};


#endif //CS655_POINTLIGHT_H
