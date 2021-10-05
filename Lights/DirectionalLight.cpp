#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(const glm::dvec3 &position, const glm::dvec3 &color, double intensity) : Light(position, color, intensity) {}
