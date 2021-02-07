#pragma once

#include "Core/Layers/Layer.h"
#include "Log/Log.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"

class TestLayer : public RUC::Layer
{
public:
	void OnAttach() override;
	void OnDetach() override;

	void OnRender() override;

private:
	std::shared_ptr<RUC::VertexArray> m_VertexArray;
};