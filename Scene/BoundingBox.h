//
// Created by Dallin Hagman on 9/21/21.
//

#ifndef CS655_BOUNDINGBOX_H
#define CS655_BOUNDINGBOX_H

#include "Common.h"

#include <Renderable/BaseRenderable.h>
#include "Rays/Ray.h"
#include "Rays/Hit.h"

class BoundingBox {
private:
    Bounds _bounds;
    std::unique_ptr<BoundingBox> _lowerChild;
    std::unique_ptr<BoundingBox> _upperChild;
    std::vector<BaseRenderable *> _objects{};
public:
    BoundingBox(Bounds bounds);
    explicit BoundingBox(const std::vector<BaseRenderable *>& objects);
    
    std::optional<std::unique_ptr<Rays::Hit>> intersect(Rays::Ray *);
    
    void subdivide(int level = 0);

    void pushObject(BaseRenderable *);

private:
    bool _intersectPlane(double& tnear, double& tfar, double o, double d, double l, double h);
    std::optional<std::unique_ptr<Rays::Hit>> _findHit(Rays::Ray *);
    std::pair<Bounds, Bounds> _getSubdividedBounds();
};


#endif //CS655_BOUNDINGBOX_H
