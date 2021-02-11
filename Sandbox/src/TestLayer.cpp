#include "TestLayer.h"

#include "Renderer/Renderer.h"

#include "Core/Timestep.h"
#include "Core/Input.h"

#include <imgui.h>
#include <gtc/matrix_transform.hpp>


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

	m_Shader.reset(RUC::Shader::Create("assets/shaders/DefaultShader.glsl"));
}

void TestLayer::OnDetach()
{
}

void TestLayer::OnUpdate()
{
	//TEMPORARY
	const float speed = 0.1f;

	if (RUC::Input::IsKeyPressed(RUC_KEY_D))
	{
		position.x += speed * RUC::Timestep::Get();
	}
}

void TestLayer::OnRender()
{

	m_VertexArray->Bind();
	m_Shader->Bind();

	//TEMPORARY
	const float scale = 0.5f;

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), glm::vec3(scale));

	m_Shader->UploadUniformMat4("u_Transform", transform);
	RUC::Renderer::Submit(m_VertexArray);
}

void TestLayer::OnImGuiRender()
{
	ImGui::Begin("Stats");
	ImGui::Text("Timestep: %f s", RUC::Timestep::Get());
	ImGui::Text("Fps: %d", (int)(1 / RUC::Timestep::Get()));
	ImGui::End();
}