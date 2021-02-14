#include "Shader.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include "Renderer.h"

namespace RUC
{
	Shader* Shader::Create(const std::string& filePath)
	{
		switch (Renderer::GetAPI())
		{
		case RenderDevice::API::OpenGL:
			return new OpenGLShader(filePath);
		}

		RUC_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
	
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (RenderDevice::GetAPI())
		{
		case RenderDevice::API::OpenGL:
			return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		RUC_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}