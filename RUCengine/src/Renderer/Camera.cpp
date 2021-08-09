#include "Camera.h"

#include <gtc/matrix_transform.hpp>

namespace RUC
{
	Camera::Camera(glm::mat4 projection)
	: m_Projection(projection), m_Position(glm::vec3(0.0f)), m_Rotation(glm::vec3(0.0f))
	{
		RecalculateView();
	}

	Camera::Camera()
		: m_Projection(glm::mat4(1.0f)), m_Position(glm::vec3(0.0f)), m_Rotation(glm::vec3(0.0f))
	{
		RecalculateView();
	}

	void Camera::RecalculateView()
	{
		auto matrix = glm::translate(glm::mat4(1.0f), m_Position);
		matrix = glm::rotate(matrix, glm::radians(m_Rotation[2]), glm::vec3(0.0f, 0.0f, 1.0f));
		matrix = glm::rotate(matrix, glm::radians(m_Rotation[1]), glm::vec3(0.0f, 1.0f, 0.0f));
		matrix = glm::rotate(matrix, glm::radians(m_Rotation[0]), glm::vec3(1.0f, 0.0f, 0.0f));
		m_View = glm::inverse(matrix);
	}
}