#include "FragmentShader.h"
#include "Shader.h"

color4_t FragmentShader::Process(const fragment_input_t& fragment)
{
	// transform to view space
	// it is already in world space
	glm::vec3 light_position = Shader::uniforms.view * glm::vec4{ Shader::uniforms.light.position, 1 };
	glm::vec3 light_direction = Shader::uniforms.view * glm::vec4{ -Shader::uniforms.light.direction, 1 };

	glm::vec3 light_dir = glm::normalize(light_position - fragment.position); // normalize light direction
	//glm::vec3 light_dir = glm::normalize(light_direction); // normalize light direction

	float intensity = std::max(0.0f, glm::dot(light_dir, fragment.normal));
	color3_t diffuse = Shader::uniforms.light.color * intensity;

	color3_t specular = color3_t{ 0 };
	if (intensity > 0)
	{
		glm::vec3 reflection = glm::reflect(-light_dir, fragment.normal);
		glm::vec3 view_dir = glm::normalize(-fragment.position);
		intensity = std::max(glm::dot(reflection, view_dir), 0.0f);
		intensity = pow(intensity, Shader::uniforms.m_material.shininess);
		specular = Shader::uniforms.m_material.specular * intensity;

	}
	color3_t color = ((Shader::uniforms.ambient + diffuse) * Shader::uniforms.m_material.albedo) + specular;

	return color4_t{ color, 1 };
	//return fragment.color;
}


