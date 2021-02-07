#pragma once

#include "VertexArray.h"

#include <glm.hpp>
#include <memory>

namespace RUC
{
	class RendererAPI
	{
	public:

		enum class API
		{
			OpenGL
		};

	public:
		static API GetAPI() { return s_RendererAPI; }

		virtual void SetClearColor(const glm::vec4& color) = 0;

		virtual void Clear() = 0;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;
	private:
		static API s_RendererAPI;
	};
}