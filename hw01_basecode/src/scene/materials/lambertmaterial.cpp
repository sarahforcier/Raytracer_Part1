#include <scene/materials/lambertmaterial.h>

LambertMaterial::LambertMaterial():Material()
{}

LambertMaterial::LambertMaterial(const glm::vec3 &color):Material(color)
{}

glm::vec3 LambertMaterial::EvaluateReflectedEnergy(const Intersection &isx, const glm::vec3 &outgoing_ray, const glm::vec3 &incoming_ray)
{
    glm::vec3 N = isx.normal;
    return glm::clamp(glm::dot(N, incoming_ray) * base_color, glm::vec3(0.0), glm::vec3(1.0));
}
