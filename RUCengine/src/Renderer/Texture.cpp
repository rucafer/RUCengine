#include "Texture.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLTexture.h"

#include "ResourceManager/ResourceManager.h"

namespace RUC
{
	ResPtr<Texture2D> Texture2D::LoadFromFile(const std::string& filePath)
	{
		switch (Renderer::GetAPI())
		{
		case RenderDevice::API::OpenGL:
			return ResourceManager::GetFromFile<OpenGLTexture2D>(filePath);
		}

		RUC_ASSERT(false, "Unknown RendererAPI");
		return ResPtr<Texture2D>();
	}

	ResPtr<Texture2D> Texture2D::Create(const std::string& name, uint32_t width, uint32_t height, unsigned char* data, size_t size, char flags)
	{
		switch (Renderer::GetAPI())
		{
		case RenderDevice::API::OpenGL:
			new OpenGLTexture2D(name, width, height, data, size, flags);
			return ResourceManager::GetByName<Texture2D>(name);
		}

		RUC_ASSERT(false, "Unknown RendererAPI");
		return ResPtr<Texture2D>();
	}
}