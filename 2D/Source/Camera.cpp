#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

void Camera::SetView(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up)
{
	m_view = glm::lookAt(eye, target, up);
}

void Camera::SetProjection(float fov, float aspect, float near, float far)
{
	m_projection = glm::perspective(glm::radians(fov), aspect, near, far);
}

glm::vec3 Camera::ModelToView(const glm::vec3& position) const
{
	// convert point from world space to view space
	return m_view * glm::vec4{ position, 1 };
}

glm::vec4 Camera::ViewToProjection(const glm::vec3& position) const
{
	// convert point from view space to projection space
	return m_projection * glm::vec4{ position, 1 };
}

glm::ivec2 Camera::ViewToScreen(const glm::vec3& position) const
{
	// convert point from vuew space to clip space (projection)
	glm::vec4 clip = m_projection * glm::vec4{ position, 1 };
	// convert projection space to ndc (-1 <-> 1)
	glm::vec3 ndc = clip / clip.w;

	float x = (ndc.x + 1) * (m_width / 2);
	float y = (1 - ndc.y) * (m_height / 2);

	return glm::ivec2(x, y);
}
