#include <raytracing/integrator.h>


Integrator::Integrator():
    max_depth(5), scene(nullptr), intersection_engine(nullptr)
{
}

bool Integrator::isShadowed(Ray r) {
    Intersection inter = intersection_engine->GetIntersection(r);
    if (inter.t > 0.0f && !inter.object_hit->material->emissive) {
        return true;
    }
    return false;
}

//Basic ray trace
glm::vec3 Integrator::TraceRay(Ray r, unsigned int depth)
{
    Intersection inter = intersection_engine->GetIntersection(r);
    glm::vec3 color = glm::vec3(0.f);
    if (inter.t > 0.f) {
        int num = 0;
        for (auto light : scene->lights) {
            glm::vec3 o = inter.point + 0.0001f * inter.normal;
            glm::vec3 d = glm::normalize(light->transform.position() - o);
            Ray light_r = Ray(o,d);
            if (!isShadowed(light_r)) {
                color += inter.object_hit->material->EvaluateReflectedEnergy(inter, glm::normalize(r.direction), d);
                num++;
            }

        }
        color = color / float (num);
    }
    return color;
}

void Integrator::SetDepth(unsigned int depth)
{
    max_depth = depth;
}
