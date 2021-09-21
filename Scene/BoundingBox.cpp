//
// Created by Dallin Hagman on 9/21/21.
//

#include "BoundingBox.h"

BoundingBox::BoundingBox(Bounds bounds): _bounds(bounds) {}

BoundingBox::BoundingBox(const std::vector<BaseRenderable *>& objects) {
    std::copy(objects.begin(), objects.end(), std::back_inserter(_objects));
    for (const auto& object : _objects) {
        auto bounds = object->getBounds();
        auto min = bounds.min;
        auto max = bounds.max;

        
    }
}

void BoundingBox::subdivide(int level = 0) {

}
