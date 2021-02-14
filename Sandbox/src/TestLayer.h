#pragma once

#include "Core/Layers/Layer.h"
#include "Log/Log.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"

class TestLayer : public RUC::Layer
{
public:
	void OnAttach() override;
	void OnDetach() override;

	void OnUpdate() override;
	void OnRender() override;
	void OnImGuiRender() override;

private:
	std::shared_ptr<RUC::VertexArray> m_VertexArray;

	std::shared_ptr<RUC::Shader> m_Shader;
	std::shared_ptr<RUC::Shader> m_TextureShader;


	//TEMPORARY
	glm::vec3 position = { -1.0f, 0.0f, 0.0f };

	std::shared_ptr<RUC::Texture> m_CheckerBoardTex;
};