#pragma once

#include "VertexArray.h"

#include <glm.hpp>
#include <memory>

namespace RUC
{
	class RenderDevice
	{
	public:

		enum class API
		{
			OpenGL
		};

	public:
		virtual void Init() = 0;

		static API GetAPI() { return s_RendererDevice; }

		virtual void SetClearColor(const glm::vec4& color) = 0;

		virtual void Clear() = 0;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

		virtual void SetViewportSize(uint32_t width, uint32_t height) = 0;
	private:
		static API s_RendererDevice;
	};
}