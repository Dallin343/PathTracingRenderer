//
// Created by Dallin Hagman on 9/21/21.
//

#include "BoundingBox.h"
#include <limits>

BoundingBox::BoundingBox(Bounds bounds): _bounds(bounds) {}

BoundingBox::BoundingBox(const std::vector<BaseRenderable *>& objects) {
    std::copy(objects.begin(), objects.end(), std::back_inserter(_objects));
    for (const auto& object : _objects) {
        auto bounds = object->getBounds();
        auto& min = bounds.min;
        auto& max = bounds.max;

        glm::bvec3 lt = bounds < _bounds;
        glm::bvec3 gt = bounds > _bounds;

        if (glm::any(lt)) {
            _bounds.min.x = lt.x ? min.x : _bounds.min.x;
            _bounds.min.y = lt.y ? min.y : _bounds.min.y;
            _bounds.min.z = lt.z ? min.z : _bounds.min.z;
        }

        if (glm::any(gt)) {
            _bounds.max.x = gt.x ? max.x : _bounds.max.x;
            _bounds.max.y = gt.y ? max.y : _bounds.max.y;
            _bounds.max.z = gt.z ? max.z : _bounds.max.z;
        }
    }
}

std::optional<std::unique_ptr<Rays::Hit>> BoundingBox::intersect(Rays::Ray *ray) {
    auto origin = ray->getOrigin();
    auto dir = ray->getDirection();

    double tNear = std::numeric_limits<double>::min();
    double tFar = std::numeric_limits<double>::max();

    if (!_intersectPlane(tNear, tFar, origin.x, dir.x, _bounds.min.x, _bounds.max.x)) {
        return std::nullopt;
    }
    if (!_intersectPlane(tNear, tFar, origin.y, dir.y, _bounds.min.y, _bounds.max.y)) {
        return std::nullopt;
    }
    if (!_intersectPlane(tNear, tFar, origin.z, dir.z, _bounds.min.z, _bounds.max.z)) {
        return std::nullopt;
    }

    auto closestHit = _findHit(ray);
    if (closestHit.has_value()) {
        return closestHit;
    }

    if (_lowerChild != nullptr) {
        auto lowerHit = _lowerChild->intersect(ray);
        if (lowerHit.has_value()) return lowerHit;
    }

    if (_upperChild != nullptr) {
        auto upperHit = _upperChild->intersect(ray);
        if (upperHit.has_value()) return upperHit;
    }

    return std::nullopt;
}

bool BoundingBox::_intersectPlane(double& tnear, double& tfar, double o, double d, double l, double h) {
    if (d == 0.0) {
        if (o < l || o > h) {
            return false;
        }
    } else {
        auto t1 = (l - o) / d;
        auto t2 = (h - o) / d;
    
        if (t1 > t2) std::swap(t1, t2);
        if (t1 > tnear) tnear = t1;
        if (t2 < tfar) tfar = t2;
        if (tnear > tfar) return false;
        if (tfar < 0.0) return false;
    }
    return true;
}

const uint8_t SUBDIVISION_LIMIT = 20;
const uint8_t MIN_OBJECTS = 1;
void BoundingBox::subdivide(int level) {

    if (level >= SUBDIVISION_LIMIT || _objects.size() <= MIN_OBJECTS) {
        return;
    }
    
    std::pair<Bounds, Bounds> childBounds = _getSubdividedBounds();
    _lowerChild = std::make_unique<BoundingBox>(childBounds.first);
    _upperChild = std::make_unique<BoundingBox>(childBounds.second);


    std::vector<BaseRenderable *> lower, upper, filtered;

    for (const auto& object : _objects) {
        if (object->getBounds() ^ childBounds.first) {
            // If object is in the lower child.
            _lowerChild->pushObject(object);
        }
        if (object->getBounds() ^ childBounds.second) {
            // If object is in the upper child.
            _upperChild->pushObject(object);
        }
    }

    _objects.clear();
    _lowerChild->subdivide(level + 1);
    _upperChild->subdivide(level + 1);
}

std::pair<Bounds, Bounds> BoundingBox::_getSubdividedBounds() {
    Bounds lowerBounds, upperBounds;
    if (_bounds.x() > _bounds.y() && _bounds.x() > _bounds.z()) {
        lowerBounds = {
            _bounds.min,
            {_bounds.min.x + _bounds.x()/2.0, _bounds.max.y, _bounds.max.z}
        };
        upperBounds = {
            {_bounds.min.x + _bounds.x()/2.0, _bounds.min.y, _bounds.min.z},
            _bounds.max
        };
    } else if (_bounds.y() > _bounds.x() && _bounds.y() > _bounds.z()) {
        lowerBounds = {
            _bounds.min,
            {_bounds.max.x, _bounds.min.y + _bounds.y()/2.0, _bounds.max.z}
        };
        upperBounds = {
            {_bounds.min.x, _bounds.min.y + _bounds.y()/2.0, _bounds.min.z},
            _bounds.max
        };
    } else {
        lowerBounds = {
            _bounds.min,
            {_bounds.max.x, _bounds.max.y, _bounds.min.z + _bounds.z()/2.0}
        };
        upperBounds = {
            {_bounds.min.x, _bounds.min.y, _bounds.min.z + _bounds.z()/2.0},
            _bounds.max
        };
    }
    return {lowerBounds, upperBounds};
}

void BoundingBox::pushObject(BaseRenderable * object) {
    _objects.push_back(object);
}

std::optional<std::unique_ptr<Rays::Hit>> BoundingBox::_findHit(Rays::Ray * ray) {
    std::optional<std::unique_ptr<Rays::Hit>> closestHit = std::nullopt;
    for (const auto &object: _objects) {
        std::optional<std::unique_ptr<Rays::Hit>> hit = object->intersect(ray);
        if (!hit.has_value()) {
            continue;
        }

        if (!closestHit.has_value()) {
            closestHit = std::move(hit);
        } else if (hit.value()->distanceTo(ray->getOrigin()) < closestHit.value()->distanceTo(ray->getOrigin())) {
            closestHit = std::move(hit);
        }
    }
    return closestHit;
}
