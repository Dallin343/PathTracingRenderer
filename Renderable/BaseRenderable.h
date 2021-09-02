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
    [[maybe_unused]] Material* _material;
public:
    explicit BaseRenderable(Material* material) : _material(material) {}

    virtual std::optional<std::shared_ptr<Rays::Hit>> Intersect(const Rays::Ray& ray) = 0;
    virtual const Material& GetMaterial() = 0;
};


#endif //CS655_BASERENDERABLE_H
