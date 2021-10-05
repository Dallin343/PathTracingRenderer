//
// Created by Dallin Hagman on 9/2/21.
//

#ifndef CS655_CAMERA_H
#define CS655_CAMERA_H

#include "Common.h"

class Camera {
private:
    glm::dvec3 _lookFrom;
    glm::dvec3 _lookAt;
    glm::dvec2 _fov;
public:
    Camera() {};
    Camera(const glm::dvec3 &lookFrom, const glm::dvec3 &lookAt, const glm::dvec2 &fov);

    const glm::dvec3 &getLookFrom() const;

    void setLookFrom(const glm::dvec3 &lookFrom);

    const glm::dvec3 &getLookAt() const;

    void setLookAt(const glm::dvec3 &lookAt);

    const glm::dvec2 &getFov() const;

    void setFov(const glm::dvec2 &fov);

    glm::dvec2 getViewportSize();
};


#endif //CS655_CAMERA_H
