#include "Buffer.h"

#include "Renderer.h"
#include "RenderDevice.h"
#include "Base.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace RUC{
	
#pragma region VertexBuffer
	
	VertexBuffer* VertexBuffer::Create(float* vertices, size_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
		}

		RUC_ASSERT(false, "Unknown renderer API");
		return nullptr;
	}

#pragma endregion

#pragma region IndexBuffer
	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL:
			return new OpenGLIndexBuffer(indices, count);
		}

		RUC_ASSERT(false, "Unknown renderer API");
		return nullptr;
	}
#pragma endregion

#pragma region BufferLayout
	void BufferLayout::CalculateOffsetAndStride()
	{
		m_Stride = 0;
		for (auto& element : m_Elements)
		{
			element.Offset = m_Stride;
			m_Stride += element.Size;
		}
	}
#pragma endregion
}