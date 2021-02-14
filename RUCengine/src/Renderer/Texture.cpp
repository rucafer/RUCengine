#include "Texture.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLTexture.h"

namespace RUC
{
	Texture2D* Texture2D::Create(const std::string& filePath)
	{
		switch (Renderer::GetAPI())
		{
		case RenderDevice::API::OpenGL:
			return new OpenGLTexture2D(filePath);
		}

		RUC_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}