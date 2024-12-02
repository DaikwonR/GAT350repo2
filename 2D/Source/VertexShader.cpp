#include "VertexShader.h"

VertexShader::uniforms_t VertexShader::uniforms =
{
	glm::mat4{ 1 }, // model
	glm::mat4{ 1 }, // view
	glm::mat4{ 1 }, // projection
	color3_t{ 1 }
};

void VertexShader::Process(const vertex_t& ivertex, vertex_output_t& overtex)
{
    glm::mat4 mvp = uniforms.projection * uniforms.view * uniforms.model;
    overtex.position = mvp * glm::vec4{ ivertex.position, 1 };

    glm::mat4 mv = uniforms.view * uniforms.model;
    overtex.normal = glm::vec3{ glm::normalize(glm::mat3{ mv } * ivertex.normal) };

    
    // transform to view space
    // it is already in world space
    glm::vec3 light_position = uniforms.view * glm::vec4{ uniforms.light.position, 1 };

    glm::vec3 vposition = mv * glm::vec4{ ivertex.position, 1 };
    glm::vec3 light_dir = glm::normalize(light_position - vposition); // normalize light direction
    float intensity = std::max(0.0f, glm::dot(light_dir, overtex.normal));
    color3_t diffuse = uniforms.light.color * intensity;
    overtex.color = uniforms.ambient + diffuse;


    //color3_t light_color{ 1, 0, 0 };

    /*glm::vec3 wposition = glm::vec4{ light_dir, 1 } * uniforms.view;
    glm::vec3 dir_light = glm::normalize(-wposition);
    float dir_intensity = std::max(0.0f, glm::dot(dir_light, overtex.normal));
    color3_t dir_diffuse = uniforms.light.color * dir_intensity;
    overtex.color = uniforms.ambient + dir_diffuse;*/

}
