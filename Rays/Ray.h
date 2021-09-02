//
// Created by Dallin Hagman on 9/2/21.
//

#ifndef CS655_RAY_H
#define CS655_RAY_H

#include "../Renderable/Common.h"
#include <glm/vec3.hpp>

namespace Rays {
    enum Type {
        Camera,
        Illumination
    };

    class Ray {
    protected:
        glm::dvec3 _origin;
        glm::dvec3 _direction;
        Type _type;
    public:
        Ray(const glm::dvec3 &origin, const glm::dvec3 &direction, const Type type);

        const glm::dvec3 &getOrigin() const;

        void setOrigin(const glm::dvec3 &origin);

        const glm::dvec3 &getDirection() const;

        void setDirection(const glm::dvec3 &direction);

        const Type &getType() const;

        void setType(const Type &type);
    };
}

#endif //CS655_RAY_H
