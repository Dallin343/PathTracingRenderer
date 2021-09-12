//
// Created by Dallin Hagman on 9/2/21.
//

#ifndef CS655_BASERENDERABLE_H
#define CS655_BASERENDERABLE_H

#include "Material.h"
#include "Rays/Ray.h"
#include "Rays/Hit.h"
#include <iostream>
#include <optional>
#include <memory>

class BaseRenderable {
protected:
    std::shared_ptr<Material> _material;
public:
    explicit BaseRenderable(std::shared_ptr<Material> material) : _material(material) {}

    virtual std::optional<std::shared_ptr<Rays::Hit>> Intersect(std::shared_ptr<Rays::Ray> ray) = 0;
    virtual std::shared_ptr<Material> GetMaterial() = 0;
};


#endif //CS655_BASERENDERABLE_H
