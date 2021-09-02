//
// Created by Dallin Hagman on 9/2/21.
//

#include "Camera.h"

Camera::Camera(const glm::dvec3 &lookFrom, const glm::dvec3 &lookAt, const glm::dvec2 &fov) : _lookFrom(lookFrom),
                                                                                              _lookAt(lookAt),
                                                                                              _fov(fov) {}

const glm::dvec3 &Camera::getLookFrom() const {
    return _lookFrom;
}

void Camera::setLookFrom(const glm::dvec3 &lookFrom) {
    _lookFrom = lookFrom;
}

const glm::dvec3 &Camera::getLookAt() const {
    return _lookAt;
}

void Camera::setLookAt(const glm::dvec3 &lookAt) {
    _lookAt = lookAt;
}

const glm::dvec2 &Camera::getFov() const {
    return _fov;
}

void Camera::setFov(const glm::dvec2 &fov) {
    _fov = fov;
}
