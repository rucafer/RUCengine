#include "Texture.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLTexture.h"

namespace RUC
{
	Texture2D* Texture2D::LoadFromFile(const std::string& filePath)
	{
		switch (Renderer::GetAPI())
		{
		case RenderDevice::API::OpenGL:
			return new OpenGLTexture2D(filePath);
		}

		RUC_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
	Texture2D* Texture2D::Create(const std::string& name, uint32_t width, uint32_t height, unsigned char* data, size_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RenderDevice::API::OpenGL:
			return new OpenGLTexture2D(name, width, height, data, size);
		}

		RUC_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}