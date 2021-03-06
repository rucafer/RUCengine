#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace RUC
{

	static GLenum ShaderDataTypeToOpenGLType(BufferDataType type)
	{
		switch (type)
		{
		case RUC::BufferDataType::Float:
		case RUC::BufferDataType::Float2:
		case RUC::BufferDataType::Float3:
		case RUC::BufferDataType::Float4:
		case RUC::BufferDataType::Mat3:
		case RUC::BufferDataType::Mat4:
			return GL_FLOAT;
		case RUC::BufferDataType::Int:
		case RUC::BufferDataType::Int2:
		case RUC::BufferDataType::Int3:
		case RUC::BufferDataType::Int4:
			return GL_INT;
		case RUC::BufferDataType::Bool:
			return GL_BOOL;
		}

		RUC_ASSERT(false, "Unknown BufferDataType");
		return 0;
	}


	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		const BufferLayout& layout = vertexBuffer->GetLayout();
		RUC_ASSERT(layout.GetElements().size(), "VertexBuffer must have a layout");

		m_VertexBuffers.push_back(vertexBuffer);

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(m_AttribIndexOffset);
			glVertexAttribPointer(m_AttribIndexOffset, element.GetComponentCount(), ShaderDataTypeToOpenGLType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*) (uint64_t) element.Offset);


			m_AttribIndexOffset++;
		}
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		m_IndexBuffer = indexBuffer;

		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();
		glBindVertexArray(0);
	}	
}