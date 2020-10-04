#pragma once

#include "Core/Layers/Layer.h"

class TestLayer : public RUC::Layer
{
public:
	void OnAttach() override;
	void OnDetach() override;

	void OnUpdate() override;
};