#include "Renderer2D.h"

#include "gtc/matrix_transform.hpp"


namespace RUC
{
	static float quadVertexPositions[4 * 6] = { -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
											    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
												 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f,
												 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f };

	static unsigned int quadIndices[6] = { 0, 1, 2, 2, 3, 0};

	static std::shared_ptr<VertexArray> quadVertexArray;

	void Renderer2D::Init()
	{
		quadVertexArray.reset(VertexArray::Create());

		std::shared_ptr<VertexBuffer> quadVertexBuffer;
		quadVertexBuffer.reset(VertexBuffer::Create(quadVertexPositions, sizeof(quadVertexPositions)));
		quadVertexBuffer->SetLayout({{ BufferDataType::Float4, "a_Position" }, 
									 { BufferDataType::Float2, "a_TexCoord" }});
		quadVertexArray->AddVertexBuffer(quadVertexBuffer);

		std::shared_ptr<IndexBuffer> quadIndexBuffer;
		quadIndexBuffer.reset(IndexBuffer::Create(quadIndices, 6));
		quadVertexArray->SetIndexBuffer(quadIndexBuffer);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec3& scale, const std::shared_ptr<Shader>& shader, const std::shared_ptr<Texture>& texture)
	{
		shader->Bind();

		glm::mat4 transform = glm::scale(glm::translate(glm::mat4(1.0f), position), scale);

		shader->UploadUniformMat4("u_Transform", transform);

		const uint32_t texSlot = 0;
		shader->UploadUniformInt("u_Texture", texSlot);

		texture->Bind(texSlot);

		Renderer::Submit(quadVertexArray);
	}
}
