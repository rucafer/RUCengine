#pragma once

#include "Core/Layers/Layer.h"

#include <imgui.h>



class ImGuiLayer : public RUC::Layer
{
public:
	ImGuiLayer() = default;

	void OnImGuiRender() override;
};