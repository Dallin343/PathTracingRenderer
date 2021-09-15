//
// Created by Dallin Hagman on 9/2/21.
//

#ifndef CS655_RAY_H
#define CS655_RAY_H

#include "../Renderable/Common.h"
#include <glm/vec3.hpp>

namespace Rays {

    class Ray {
    protected:
        glm::dvec3 _origin;
        glm::dvec3 _direction;
    public:
        Ray(const glm::dvec3 &origin, const glm::dvec3 &direction);

        const glm::dvec3 &getOrigin() const;

        void setOrigin(const glm::dvec3 &origin);

        const glm::dvec3 &getDirection() const;

        void setDirection(const glm::dvec3 &direction);
    };

    class CameraRay: public Ray {
    public:
        CameraRay(const glm::dvec3 &origin, const glm::dvec3 &direction): Ray(origin, direction) {}
    };
    class IlluminationRay: public Ray {
    public:
        IlluminationRay(const glm::dvec3 &origin, const glm::dvec3 &direction): Ray(origin, direction) {}
    };
    class ReflectionRay: public Ray {
    public:
        ReflectionRay(const glm::dvec3 &origin, const glm::dvec3 &direction): Ray(origin, direction) {}
    };
    class TransmissionRay: public Ray {
    public:
        TransmissionRay(const glm::dvec3 &origin, const glm::dvec3 &direction): Ray(origin, direction) {}
    };
    class ShadowRay: public Ray {
    public:
        ShadowRay(const glm::dvec3 &origin, const glm::dvec3 &direction): Ray(origin, direction) {}
    };
}

#endif //CS655_RAY_H
