//
// Created by Dallin Hagman on 9/2/21.
//

#ifndef CS655_LIGHT_H
#define CS655_LIGHT_H

#include <glm/vec3.hpp>
#include <memory>
#include <Scene/SceneDescription.h>
#include "Renderable/BaseRenderable.h"
#include "Rays/Ray.h"
#include "Renderable/Material.h"
#include "Scene/Camera.h"
#include "Rays/Hit.h"

class Light {
protected:
    glm::dvec3 _position;
    glm::dvec3 _color;

    virtual bool _inShadow(const std::unique_ptr<Rays::IlluminationRay>&, const std::vector<std::shared_ptr<BaseRenderable>>&) = 0;
public:
    Light(const glm::dvec3 &position, const glm::dvec3 &color);

    virtual glm::dvec3 calculateDiffuse(const std::shared_ptr<Rays::Ray> &, const std::shared_ptr<Rays::Hit> &,
                                const std::shared_ptr<Material> &, const std::shared_ptr<SceneDescription>&) = 0;

    virtual glm::dvec3 calculateSpecular(const std::shared_ptr<Rays::Ray> &, const std::shared_ptr<Rays::Hit> &,
                                 const std::shared_ptr<Material> &, const std::shared_ptr<SceneDescription>&) = 0;

    const glm::dvec3 &getPosition() const;

    void setPosition(const glm::dvec3 &position);

    const glm::dvec3 &getColor() const;

    void setColor(const glm::dvec3 &color);
};


#endif //CS655_LIGHT_H
