//
// Created by Dallin Hagman on 9/2/21.
//

#ifndef CS655_BASERENDERABLE_H
#define CS655_BASERENDERABLE_H

#include "Common.h"
#include <iostream>

#include "Material/Material.h"
#include "Rays/Ray.h"
#include "Rays/Hit.h"


class BaseRenderable {
protected:
    const std::unique_ptr<Material> &_material;
    Bounds _bounds{};
public:
    explicit BaseRenderable(const std::unique_ptr<Material> &material) : _material(material) {}

    virtual std::optional<std::unique_ptr<Rays::Hit>> intersect(const Rays::Ray *ray) = 0;

    const Material *getMaterial() {
        return _material.get();
    };

    const Bounds &getBounds() const {
        return _bounds;
    }
};


#endif //CS655_BASERENDERABLE_H
