#include "Renderer.h"

namespace RUC
{

	std::vector<std::shared_ptr<FrameBuffer>> Renderer::s_ResizableFrameBuffers;

	void Renderer::Init()
	{
		RenderCommand::Init();
	}

	void Renderer::BeginScene()
	{

	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		RenderCommand::DrawIndexed(vertexArray);
	}

	void Renderer::SetViewportSize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewportSize(width, height);
	}
}