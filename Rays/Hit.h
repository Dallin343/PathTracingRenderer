//
// Created by Dallin Hagman on 9/2/21.
//

#ifndef CS655_HIT_H
#define CS655_HIT_H

#include "Common.h"

class BaseRenderable;

namespace Rays {
    class Hit {
    private:
        double _t;
        glm::dvec3 _point;
        glm::dvec3 _norm;
        BaseRenderable *_object;

        glm::dvec2 _texCoords{};
    public:
        Hit(double t, const glm::dvec3 &point, const glm::dvec3 &norm, BaseRenderable *object);

        Hit(double t, const glm::dvec3 &point, const glm::dvec3 &norm, const glm::dvec2 &texCoords,
            BaseRenderable *object);

        double getT() const;

        void setT(double t);

        const glm::dvec3 &getPoint() const;

        void setPoint(const glm::dvec3 &point);

        const glm::dvec3 &getNorm() const;

        void setNorm(const glm::dvec3 &norm);

        double distanceTo(const glm::dvec3 &other);

        glm::dvec3 vectorTo(const glm::dvec3 &other);

        BaseRenderable *getObject() const;

        void setObject(BaseRenderable *object);

        const glm::dvec2 &getTexCoords() const;
    };
}

#endif //CS655_HIT_H
