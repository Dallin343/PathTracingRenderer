//
// Created by Dallin Hagman on 9/2/21.
//

#include "SceneDescription.h"

#include <utility>

SceneDescription::SceneDescription() = default;

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

std::shared_ptr<Camera> SceneDescription::getCamera() const {
    return _camera;
}

void SceneDescription::setCamera(std::shared_ptr<Camera> camera) {
    _camera = std::move(camera);
}

const std::vector<std::shared_ptr<BaseRenderable>> &SceneDescription::getObjects() const {
    return _objects;
}


const std::vector<std::shared_ptr<Light>> &SceneDescription::getLights() const {
    return _lights;
}

void SceneDescription::pushObject(const std::shared_ptr<BaseRenderable>& object) {
    _objects.push_back(object);
}

void SceneDescription::pushLight(const std::shared_ptr<Light>& light) {
    _lights.push_back(light);
}

void SceneDescription::insertMaterial(int num, const std::shared_ptr<Material>& material) {
    _materials.insert(std::make_pair(num, material));
}

const std::unordered_map<int, std::shared_ptr<Material>> &SceneDescription::getMaterials() const {
    return _materials;
}
