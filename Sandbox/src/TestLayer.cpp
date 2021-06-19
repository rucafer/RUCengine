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

	/*m_VertexArray.reset(RUC::VertexArray::Create());
	m_VertexArray->AddVertexBuffer(vertexPosBuffer);
	m_VertexArray->AddVertexBuffer(vertexColorBuffer);
	m_VertexArray->SetIndexBuffer(indexBuffer);

	m_Shader = RUC::Shader::LoadFromFile("assets/shaders/Test.glsl");
	m_TextureShader =RUC::Shader::LoadFromFile("assets/shaders/TextureShader.glsl");
	m_CheckerBoardTex = RUC::Texture2D::LoadFromFile("assets/textures/TestCheckerBoard.png");



	//TEMPORARY: should be fixed whit persistent resources
	unsigned char* whiteTextureData = new unsigned char[1 * 1 * 3];

	whiteTextureData[0] = (char)255;
	whiteTextureData[1] = (char)255;
	whiteTextureData[2] = (char)255;

	auto temporary = RUC::Texture2D::Create("EmptyTexture", 1, 1, whiteTextureData, 1 * 1 * 3);

	mat =RUC::Material::Create("test", m_TextureShader);

	mat->SetTexture2D("u_Texture", m_CheckerBoardTex);*/

	/*RUC_INFO("===== ResPtr test =====");
	RUC_INFO("Asset creation:")
	RUC::ResPtr<RUC::Texture2D> testA = RUC::Texture2D::LoadFromFile("assets/textures/TestCheckerBoard.png");
	RUC_INFO("New scope");
	{
		RUC_INFO("Asset copy:")
		RUC::ResPtr<RUC::Texture2D> b = testA;
	}
	RUC_INFO("Scope ended");
	RUC_INFO("===== ResPtr test =====");*/

	{
		RUC::ResPtr<RUC::Texture2D> testA = RUC::Texture2D::LoadFromFile("assets/textures/TestCheckerBoard.png");
		RUC::ResPtr<RUC::Texture2D> testB = RUC::Texture2D::LoadFromFile("assets/textures/TestCheckerBoard2.png");
	}
	{
		RUC::ResPtr<RUC::Texture2D> testA = RUC::Texture2D::LoadFromFile("assets/textures/TestCheckerBoard3.png");
		RUC::ResPtr<RUC::Texture2D> testB = RUC::Texture2D::LoadFromFile("assets/textures/TestCheckerBoard4.png");
		RUC::ResPtr<RUC::Texture2D> testC = RUC::Texture2D::LoadFromFile("assets/textures/TestCheckerBoard5.png");
	}
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
	
	
	/*m_Shader->Bind();
	//TEMPORARY
	const float scale = 0.5f;

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), glm::vec3(scale));

	m_Shader->UploadUniformMat4("u_Transform", transform);
	RUC::Renderer::Submit(m_VertexArray);

	RUC::Renderer2D::DrawQuad(glm::vec3(0.0f), glm::vec3(1.0f), mat);*/

	m_FrameBuffer->Unbind();
}

void TestLayer::OnImGuiRender()
{
	m_TimeCounter += RUC::Timestep::Get();
	m_FrameCounter++;

	if (m_TimeCounter >= 1.0)
	{
		m_TimeCounter = 0.0;
		m_LastFPS = m_FrameCounter;
		m_FrameCounter = 0;
	}

	ImGui::Begin("Stats");
	ImGui::Text("Fps: %d", m_LastFPS);
	ImGui::End();
}