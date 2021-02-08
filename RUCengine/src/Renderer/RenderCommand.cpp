#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRenderDevice.h"

namespace RUC
{
	RenderDevice* RenderCommand::s_RendererAPI = nullptr;

	void RenderCommand::Init()
	{
		switch (RenderDevice::GetAPI())
		{
		case RenderDevice::API::OpenGL:
			s_RendererAPI = new OpenGLRenderDevice();
			break;
		default:
			RUC_ASSERT(false, "Unknown RendererAPI");
		}
	}

	void RenderCommand::SetClearColor(const glm::vec4& color)
	{
		s_RendererAPI->SetClearColor(color);
	}

	void RenderCommand::Clear()
	{
		s_RendererAPI->Clear();
	}

	void RenderCommand::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
	{
		s_RendererAPI->DrawIndexed(vertexArray);
	}
}