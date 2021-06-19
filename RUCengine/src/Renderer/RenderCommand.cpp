#include "RenderCommand.h"

#include "Renderer2D.h"

#include "Platform/OpenGL/OpenGLRenderDevice.h"

#include "ResourceManager/ResourceManager.h"

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

		unsigned char* whiteTextureData = new unsigned char[1 * 1 * 3];

		whiteTextureData[0] = (char)255;
		whiteTextureData[1] = 0;
		whiteTextureData[2] = 0;

		//Texture2D::Create("EmptyTexture", 1, 1, whiteTextureData, 1 * 1 * 3);
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