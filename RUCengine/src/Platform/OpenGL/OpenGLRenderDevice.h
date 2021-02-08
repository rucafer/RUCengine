#pragma once

#include "Renderer/RenderDevice.h"

namespace RUC
{
	class OpenGLRenderDevice : public RenderDevice
	{
	public:
		void SetClearColor(const glm::vec4& color) override;

		void Clear() override;

		void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};
}