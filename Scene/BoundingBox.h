//
// Created by Dallin Hagman on 9/21/21.
//

#ifndef CS655_BOUNDINGBOX_H
#define CS655_BOUNDINGBOX_H

#include "Common.h"
#include <vector>
#include <Renderable/BaseRenderable.h>

class BoundingBox {
private:
    Bounds _bounds;
    std::vector<std::unique_ptr<BoundingBox>> _children{};
    std::vector<BaseRenderable *> _objects{};
public:
    BoundingBox(Bounds bounds);
    explicit BoundingBox(const std::vector<BaseRenderable *>& objects);
    void subdivide(int level);
};


#endif //CS655_BOUNDINGBOX_H
