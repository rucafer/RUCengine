#pragma once

#include "RenderDevice.h"
#include "RenderCommand.h"

#include "VertexArray.h"

#include "FrameBuffer.h"

#include "Material.h"

namespace RUC
{
	class Renderer
	{
	public:
		static RenderDevice::API GetAPI() { return RenderDevice::GetAPI(); }

		static void Init();

		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

		static void SetViewportSize(uint32_t width, uint32_t height);
	private:
		static std::vector<std::shared_ptr<FrameBuffer>> s_ResizableFrameBuffers;
	};
}