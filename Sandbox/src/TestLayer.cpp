#include "TestLayer.h"

#include "Renderer/Renderer.h"

void TestLayer::OnAttach()
{

	float vertexPos[3 * 3] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	float vertexColor[3 * 4] = {
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f
	};

	unsigned int indices[3] = { 0, 1, 2 };

	std::shared_ptr<RUC::VertexBuffer> vertexPosBuffer;
	std::shared_ptr<RUC::VertexBuffer> vertexColorBuffer;
	std::shared_ptr<RUC::IndexBuffer> indexBuffer;

	vertexPosBuffer.reset(RUC::VertexBuffer::Create(vertexPos, sizeof(vertexPos)));
	vertexColorBuffer.reset(RUC::VertexBuffer::Create(vertexColor, sizeof(vertexColor)));

	RUC::BufferLayout posLayout = {
		{RUC::ShaderDataType::Float3, "a_Positon"}
	};
	RUC::BufferLayout colorLayout = {
		{RUC::ShaderDataType::Float4, "a_Color"}
	};
	vertexPosBuffer->SetLayout(posLayout);
	vertexColorBuffer->SetLayout(colorLayout);

	indexBuffer.reset(RUC::IndexBuffer::Create(indices, 3));

	m_VertexArray.reset(RUC::VertexArray::Create());
	m_VertexArray->AddVertexBuffer(vertexPosBuffer);
	m_VertexArray->AddVertexBuffer(vertexColorBuffer);
	m_VertexArray->SetIndexBuffer(indexBuffer);

}

void TestLayer::OnDetach()
{
}

void TestLayer::OnRender()
{
	m_VertexArray->Bind();
	//glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	RUC::Renderer::Submit(m_VertexArray);
}