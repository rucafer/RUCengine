#include "RenderCommand.h"

#include "Renderer2D.h"

#include "Platform/OpenGL/OpenGLRenderDevice.h"

namespace RUC
{
	RenderDevice* RenderCommand::s_RendererDevice = nullptr;

	void RenderCommand::Init()
	{
		switch (RenderDevice::GetAPI())
		{
		case RenderDevice::API::OpenGL:
			s_RendererDevice = new OpenGLRenderDevice();
			break;
		default:
			RUC_ASSERT(false, "Unknown RendererAPI");
		}

		s_RendererDevice->Init();
		Renderer2D::Init();
	}

	void RenderCommand::SetClearColor(const glm::vec4& color)
	{
		s_RendererDevice->SetClearColor(color);
	}

	void RenderCommand::Clear()
	{
		s_RendererDevice->Clear();
	}

	void RenderCommand::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
	{
		s_RendererDevice->DrawIndexed(vertexArray);
	}

	void RenderCommand::SetViewportSize(uint32_t width, uint32_t height)
	{
		s_RendererDevice->SetViewportSize(width, height);
	}
}