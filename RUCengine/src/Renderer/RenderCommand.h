#pragma once

#include "RenderDevice.h"

#include "VertexArray.h"

namespace RUC
{
	class RenderCommand
	{
	public:
		static void Init();
		
		static void SetClearColor(const glm::vec4& color);

		static void Clear();

		static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray);

		static void SetViewportSize(uint32_t width, uint32_t height);

	private:
		static RenderDevice* s_RendererDevice;
	};
}