#include "FrameBuffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLFrameBuffer.h"

namespace RUC
{
	std::vector<FrameBuffer*> FrameBuffer::s_ResizableFrameBuffers;

	FrameBuffer* FrameBuffer::Create(const FrameBufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
		case RenderDevice::API::OpenGL:		return new OpenGLFrameBuffer(spec);
		}

		RUC_ASSERT(false, "Unknonwn RendererAPI");
		return nullptr;
	}

	void FrameBuffer::ResizeAllResizables(uint32_t width, uint32_t height)
	{
		for (FrameBuffer* fb : s_ResizableFrameBuffers)
		{
			fb->Resize(width, height);
		}
	}
}