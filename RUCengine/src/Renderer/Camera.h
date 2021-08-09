#pragma once

#include <glm.hpp>

namespace RUC
{
	class Camera
	{
	public:
		~Camera() = default;
		Camera();

		void SetPosition(const glm::vec3& position) { m_Position = position; }
		void SetRotation(const glm::vec3& rotation) { m_Rotation = rotation; }

		glm::vec3 getPosition() const { return m_Position; }
		glm::vec3 getRotation() const { return m_Rotation; }

		glm::mat4 getViewMatrix() const { return m_View; }
		glm::mat4 getProjectionMatrix() const { return m_Projection; }
		glm::mat4 getViewProjectionMatrix() const { return m_View * m_Projection; }

	protected:
		Camera(glm::mat4 projection);

		void RecalculateView();
	
		glm::vec3 m_Position;
		glm::vec3 m_Rotation;

		glm::mat4 m_Projection;
		glm::mat4 m_View;
	};
}