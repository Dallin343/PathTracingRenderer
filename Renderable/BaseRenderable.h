//
// Created by Dallin Hagman on 9/2/21.
//

#ifndef CS655_BASERENDERABLE_H
#define CS655_BASERENDERABLE_H

#include "Material/Material.h"
#include "Rays/Ray.h"
#include "Rays/Hit.h"
#include <iostream>
#include <optional>
#include <memory>

class BaseRenderable {
protected:
    const std::unique_ptr<Material>& _material;
public:
    explicit BaseRenderable(const std::unique_ptr<Material>& material) : _material(material) {}

    virtual std::optional<std::unique_ptr<Rays::Hit>> intersect(const Rays::Ray* ray) = 0;
    virtual const Material* getMaterial() = 0;
};


#endif //CS655_BASERENDERABLE_H
