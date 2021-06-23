#include "Shader.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include "Renderer.h"

namespace RUC
{
	ResPtr<Shader> Shader::LoadFromFile(const std::string& filePath)
	{
		switch (Renderer::GetAPI())
		{
		case RenderDevice::API::OpenGL:
			auto resPtr = ResourceManager::GetFromFile<OpenGLShader>(filePath);
			return resPtr;
		}

		RUC_ASSERT(false, "Unknown RendererAPI");
		return ResPtr<Shader>();
	}
	
	ResPtr<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (RenderDevice::GetAPI())
		{
		case RenderDevice::API::OpenGL:
			new OpenGLShader(name, vertexSrc, fragmentSrc);
			return ResourceManager::GetByName<Shader>(name);
		}

		RUC_ASSERT(false, "Unknown RendererAPI");
		return ResPtr<Shader>();
	}
}