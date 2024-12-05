#include "VertexShader.h"
#include "Framebuffer.h"
#include "Shader.h"

#define GOURAUD

void VertexShader::Process(const vertex_t& ivertex, vertex_output_t& overtex)
{
    glm::mat4 mvp = Shader::uniforms.projection * Shader::uniforms.view * Shader::uniforms.model;
    overtex.position = mvp * glm::vec4{ ivertex.position, 1 };

    glm::mat4 mv = Shader::uniforms.view * Shader::uniforms.model;
    overtex.normal = glm::vec3{ glm::normalize(glm::mat3{ mv } * ivertex.normal) };

    overtex.vposition = mv * glm::vec4{ ivertex.position, 1 };

#ifdef GOURAUD
    
    // transform to view space
    // it is already in world space
    glm::vec3 light_position = Shader::uniforms.view * glm::vec4{ Shader::uniforms.light.position, 1 };

    glm::vec3 vposition = mv * glm::vec4{ ivertex.position, 1 };
    glm::vec3 light_dir = glm::normalize(light_position - vposition); // normalize light direction
    float intensity = std::max(0.0f, glm::dot(light_dir, overtex.normal));
    color3_t diffuse = Shader::uniforms.light.color * intensity;
    


    /*glm::vec3 wposition = glm::vec4{ light_dir, 1 } * Shader::uniforms.view;
    glm::vec3 dir_light = glm::normalize(-wposition);
    float dir_intensity = std::max(0.0f, glm::dot(dir_light, overtex.normal));
    color3_t dir_diffuse = Shader::uniforms.light.color * dir_intensity;
    overtex.color = Shader::uniforms.ambient + dir_diffuse;*/

    color3_t specular = color3_t{ 0 };
    if (intensity > 0)
    {
        glm::vec3 reflection = glm::reflect(-light_dir, overtex.normal);
        glm::vec3 view_dir = glm::normalize(overtex.position);
        intensity = std::max(glm::dot(reflection, view_dir), 0.0f);
        intensity = pow(intensity, Shader::uniforms.m_material.shininess);
        specular = Shader::uniforms.m_material.specular * intensity;

    }

    overtex.color = ((Shader::uniforms.ambient + diffuse) * Shader::uniforms.m_material.albedo) + specular;

#endif // 0



}
