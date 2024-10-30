#include "Material.h"
#include "Random.h"

bool Lambertian::Scatter(const ray_t& ray, const raycastHit_t& raycastHit, color3_t& attenuation, ray_t& scattered)
{
    scattered.origin = raycastHit.point;
    scattered.direction = raycastHit.normal + randomOnUnitSphere();
    attenuation = m_albedo;

    return false;
}

bool Metal::Scatter(const ray_t& ray, const raycastHit_t& raycastHit, color3_t& attenuation, ray_t& scattered)
{
    glm::vec3 reflected = Reflect(ray.direction, glm::normalize(raycastHit.normal));
    scattered = ray_t{ raycastHit.point, reflected + (randomOnUnitSphere() * m_fuzz) };
    attenuation = m_albedo;

    return glm::dot(scattered.direction, raycastHit.normal) > 0;
}

bool Dielectric::Scatter(const ray_t& ray, const raycastHit_t& raycastHit, color3_t& attenuation, ray_t& scattered)
{
    glm::vec3 outNormal;
    float ni_over_nt;
    float cosine;

    // check if we are hitting from the outside
    if (glm::dot(ray.direction, raycastHit.normal) < 0)
    {
        outNormal = raycastHit.normal;
        ni_over_nt = 1.0f / m_refractiveIndex;
        cosine = -glm::dot(ray.direction, raycastHit.normal) / ray.direction.length();
    }
    else
    {
        // hitting from the inside

        outNormal = -raycastHit.normal;
        ni_over_nt = m_refractiveIndex;
        cosine = m_refractiveIndex * (glm::dot(ray.direction, raycastHit.normal) / ray.direction.length());

    }

    glm::vec3 refracted;
    float reflectProbability = 1.0f;

    if (Refract(ray.direction, raycastHit.normal, m_refractiveIndex, refracted))
    {
        reflectProbability = Schlick(cosine, m_refractiveIndex);
    }
    glm::vec3 reflected = Reflect(ray.direction, raycastHit.normal);

    scattered = (randomf() < reflectProbability) ? ray_t{ raycastHit.point, reflected } : ray_t{ raycastHit.point, refracted };

    attenuation = m_albedo;

    return true;
}

bool Emissive::Scatter(const ray_t& ray, const raycastHit_t& raycastHit, color3_t& attenuation, ray_t& scattered)
{

    return false;
}

