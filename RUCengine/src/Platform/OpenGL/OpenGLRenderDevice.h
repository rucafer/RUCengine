#pragma once

#include "Renderer/RenderDevice.h"

namespace RUC
{
	class OpenGLRenderDevice : public RenderDevice
	{
	public:
		void Init() override;

		void SetClearColor(const glm::vec4& color) override;

		void Clear() override;

		void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;

		void SetViewportSize(uint32_t width, uint32_t height) override;
	};
}