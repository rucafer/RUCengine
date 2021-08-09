#include "OrthographicCamera.h"

#include <gtc/matrix_transform.hpp>

namespace RUC
{
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float near, float far)
	{
		m_Left = left;
		m_Right = right;

		m_Bottom = bottom;
		m_Top = top;

		m_Near = near;
		m_Far = far;

		RecalculateProjection();
	}

	OrthographicCamera::OrthographicCamera()
		:Camera(glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -10.0f, 10.0f))
	{
		m_Left = -1.0f;
		m_Right = 1.0f;

		m_Bottom = -1.0f;
		m_Top = 1.0f;

		m_Near = -10.0f;
		m_Far = 10.0f;

		RecalculateProjection();
	}

	void OrthographicCamera::SetProjection(float right, float left, float bottom, float top, float near, float far)
	{
		m_Right = right;
		m_Left = left;

		m_Bottom = bottom;
		m_Top = top;

		m_Near = near;
		m_Far = far;

		RecalculateProjection();
	}

	void OrthographicCamera::RecalculateProjection()
	{
		m_Projection = glm::ortho(m_Left, m_Right, m_Bottom, m_Top, m_Near, m_Far);
	}
}