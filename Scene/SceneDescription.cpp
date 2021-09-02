//
// Created by Dallin Hagman on 9/2/21.
//

#include "SceneDescription.h"

SceneDescription::SceneDescription() {}

const glm::dvec3 &SceneDescription::getBackground() const {
    return _background;
}

void SceneDescription::setBackground(const glm::dvec3 &background) {
    _background = background;
}

const glm::dvec3 &SceneDescription::getAmbientColor() const {
    return _ambientColor;
}

void SceneDescription::setAmbientColor(const glm::dvec3 &ambientColor) {
    _ambientColor = ambientColor;
}

double SceneDescription::getAmbientFac() const {
    return _ambientFac;
}

void SceneDescription::setAmbientFac(double ambientFac) {
    _ambientFac = ambientFac;
}

const Camera &SceneDescription::getCamera() const {
    return _camera;
}

void SceneDescription::setCamera(const Camera &camera) {
    _camera = camera;
}

const std::vector<std::unique_ptr<BaseRenderable>> &SceneDescription::getObjects() const {
    return _objects;
}

void SceneDescription::setObjects(const std::vector<std::unique_ptr<BaseRenderable>> &objects) {
    _objects = objects;
}

const std::vector<std::unique_ptr<Light>> &SceneDescription::getLights() const {
    return _lights;
}

void SceneDescription::setLights(const std::vector<std::unique_ptr<Light>> &lights) {
    _lights = lights;
}
