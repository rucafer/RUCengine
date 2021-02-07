#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace RUC
{

	static GLenum ShaderDataTypeToOpenGLType(ShaderDataType type)
	{
		switch (type)
		{
		case RUC::ShaderDataType::Float:
		case RUC::ShaderDataType::Float2:
		case RUC::ShaderDataType::Float3:
		case RUC::ShaderDataType::Float4:
		case RUC::ShaderDataType::Mat3:
		case RUC::ShaderDataType::Mat4:
			return GL_FLOAT;
		case RUC::ShaderDataType::Int:
		case RUC::ShaderDataType::Int2:
		case RUC::ShaderDataType::Int3:
		case RUC::ShaderDataType::Int4:
			return GL_INT;
		case RUC::ShaderDataType::Bool:
			return GL_BOOL;
		}

		RUC_ASSERT(false, "Unknown ShaderDataType");
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
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		m_IndexBuffer = indexBuffer;

		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();
	}	
}