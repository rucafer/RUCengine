#pragma once

#include "Camera.h"

namespace RUC
{
	class OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera(float right, float left, float bottom, float top, float near, float far);
		OrthographicCamera();

		void SetProjection(float right, float left, float bottom, float top, float near, float far);

		float GetRight() const { return m_Right; }
		float GetLeft() const { return m_Left; }

		float GetBottom() const { return m_Bottom; }
		float GetTop() const { return m_Top; }

		float GetNear() const { return m_Near; }
		float GetFar() const { return m_Far; }

		void SetRight(float right) { m_Right = right; RecalculateProjection(); }
		void SetLeft(float left) { m_Left = left; RecalculateProjection(); }

		void SetBottom(float bottom) { m_Bottom = bottom; RecalculateProjection();  }
		void SetTop(float top) { m_Top = top; RecalculateProjection(); }
		
		void SetNear(float nearValue) { m_Near= nearValue; RecalculateProjection(); }
		void SetFar(float farValue) { m_Far = farValue; RecalculateProjection(); }

	private:
		void RecalculateProjection();

	private:
		float m_Right, m_Left;
		float m_Bottom, m_Top;
		float m_Near, m_Far;
	};
}
