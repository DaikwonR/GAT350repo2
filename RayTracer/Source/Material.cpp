#include "Material.h"
#include "Random.h"

bool Lambertian::Scatter(const ray_t& ray, const raycastHit_t& raycastHit, color3_t& attenuation, ray_t& scattered)
{
    scattered.origin = raycastHit.point;
    scattered.direction = raycastHit.normal + randomOnUnitSphere();
    attenuation = m_albedo;

    return false;
}
