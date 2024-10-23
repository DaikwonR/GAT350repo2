#include "Camera.h"
#include "MathUtils.h"

#include <glm/gtc/matrix_transform.hpp>

void Camera::SetView(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up)
{
	m_eye = eye;

	m_forward = glm::normalize(target - eye);
	m_right = glm::normalize(Cross(up, m_forward));
	m_up = Cross(m_forward, m_right);
}

ray_t

void Camera::CalculateViewPlane()
{
	float theta = glm::radians(m_fov);

	float halfHeight = glm::tan(theta * 0.5f);
	float height = halfHeight * 2;
	float width = height * m_aspectRatio;
}

