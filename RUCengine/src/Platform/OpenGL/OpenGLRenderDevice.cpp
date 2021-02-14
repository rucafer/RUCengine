#include "Platform/OpenGL/OpenGLRenderDevice.h"

#include <glad/glad.h>

namespace RUC
{
	void OpenGLMessageCallback(unsigned source, unsigned type, unsigned id, unsigned severity,
								int length, const char* message, const void* userParam)	{
		switch (severity)
		{
			case GL_DEBUG_SEVERITY_HIGH:         RUC_ERROR(message); return;
			case GL_DEBUG_SEVERITY_MEDIUM:       RUC_ERROR(message); return;
			case GL_DEBUG_SEVERITY_LOW:          RUC_WARN(message); return;
			case GL_DEBUG_SEVERITY_NOTIFICATION: RUC_TRACE(message); return;
		}
	}

	void OpenGLRenderDevice::Init()
	{
#ifdef RUC_DEBUG
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(OpenGLMessageCallback, nullptr);

		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
#endif
	}

	void OpenGLRenderDevice::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRenderDevice::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRenderDevice::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}