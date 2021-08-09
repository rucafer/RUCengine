#include "TestLayer.h"

#include "Renderer/Renderer.h"
#include "Renderer/Renderer2D.h"

#include "Core/Timestep.h"
#include "Core/Input.h"

#include "ResourceManager/ResourceManager.h"

#include <imgui.h>
#include <gtc/matrix_transform.hpp>

#include <glad/glad.h>


void TestLayer::OnAttach()
{
	RUC::FrameBufferSpecification fbSpec;
	fbSpec.Width = 1280;
	fbSpec.Height = 720;
	fbSpec.SwapChainTarget = true;
	fbSpec.resizable = true;
	fbSpec.AttachmentList = { RUC::FrameBufferTextureFormat::RGBA8, RUC::FrameBufferTextureFormat::DEPTH24STENCIL8 };
	m_FrameBuffer.reset(RUC::FrameBuffer::Create(fbSpec));

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
		{RUC::BufferDataType::Float3, "a_Positon"}
	};
	RUC::BufferLayout colorLayout = {
		{RUC::BufferDataType::Float4, "a_Color"}
	};
	vertexPosBuffer->SetLayout(posLayout);
	vertexColorBuffer->SetLayout(colorLayout);

	indexBuffer.reset(RUC::IndexBuffer::Create(indices, 3));

	m_VertexArray.reset(RUC::VertexArray::Create());
	m_VertexArray->AddVertexBuffer(vertexPosBuffer);
	m_VertexArray->AddVertexBuffer(vertexColorBuffer);
	m_VertexArray->SetIndexBuffer(indexBuffer);

	m_Shader = RUC::Shader::LoadFromFile("assets/shaders/Test.glsl");
	m_TextureShader =RUC::Shader::LoadFromFile("assets/shaders/TextureShader.glsl");
	m_CheckerBoardTex = RUC::Texture2D::LoadFromFile("assets/textures/TestCheckerBoard.png");

	mat =RUC::Material::Create("test", m_TextureShader);

	mat->SetTexture2D("u_Texture", m_CheckerBoardTex);

	m_Camera = RUC::OrthographicCamera(-1.0f, 1.0f, -1.0f, 1.0f, -100.0f, 100.0f);
}

void TestLayer::OnDetach()
{
}

void TestLayer::OnUpdate()
{
	//TEMPORARY
	const float speed = 0.5f;

	if (RUC::Input::IsKeyPressed(RUC_KEY_D))
	{
		position.x += speed * RUC::Timestep::Get();
	}
}

void TestLayer::OnRender()
{

	m_FrameBuffer->Bind();
	RUC::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	RUC::RenderCommand::Clear();
	
	
	//m_Shader->Bind();
	mat->SetMat4("u_ViewProjection", m_Camera.getProjectionMatrix());
	//m_TextureShader->Bind();
	//m_TextureShader->UploadUniformMat4("u_ViewProjection", m_Camera.getProjectionMatrix());

	RUC::Renderer2D::DrawQuad(glm::vec3(0.0f), glm::vec3(1.0f), mat);
	/*RUC_INFO("\t{0}\t{1}\t{2}\t{3}", a[0][0], a[0][1], a[0][2], a[0][3]);
	RUC_INFO("\t{0}\t{1}\t{2}\t{3}", a[1][0], a[1][1], a[1][2], a[1][3]);
	RUC_INFO("\t{0}\t{1}\t{2}\t{3}", a[2][0], a[2][1], a[2][2], a[2][3]);
	RUC_INFO("\t{0}\t{1}\t{2}\t{3}", a[3][0], a[3][1], a[3][2], a[3][3]);*/

	/*
	//TEMPORARY
	const float scale = 0.5f;

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), glm::vec3(scale));

	m_Shader->UploadUniformMat4("u_Transform", transform);
	RUC::Renderer::Submit(m_VertexArray);

	RUC::Renderer2D::DrawQuad(glm::vec3(0.0f), glm::vec3(1.0f), mat);
	*/

	m_FrameBuffer->Unbind();
}

void TestLayer::OnImGuiRender()
{
	m_TimeCounter += RUC::Timestep::Get();
	m_FrameCounter++;

	if (m_TimeCounter >= 0.2)
	{
		m_TimeCounter = 0.0;
		m_LastFPS = m_FrameCounter * 5;
		m_FrameCounter = 0;
	}

	ImGui::Begin("Stats");
	ImGui::Text("Fps: %d", m_LastFPS);
	ImGui::End();

	float m_Right = m_Camera.GetRight();
	float m_Left = m_Camera.GetLeft();
	float m_Top = m_Camera.GetTop();
	float m_Bottom = m_Camera.GetBottom();
	float m_Near = m_Camera.GetNear();
	float m_Far = m_Camera.GetFar();

	ImGui::Begin("Orthographic camera test");
	ImGui::InputFloat("Right", &m_Right, 0.01f);
	ImGui::InputFloat("Left", &m_Left, 0.01f);
	ImGui::InputFloat("Bottom", &m_Top, 0.01f);
	ImGui::InputFloat("Top", &m_Bottom, 0.01f);
	ImGui::InputFloat("Near", &m_Near, 0.01f);
	ImGui::InputFloat("Far", &m_Far, 0.01f);
	ImGui::End();

	m_Camera.SetProjection(m_Right, m_Left, m_Bottom, m_Top, m_Near, m_Far);
}