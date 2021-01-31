#pragma once

#include "Core/Layers/Layer.h"
#include "Log/Log.h"

class TestLayer : public RUC::Layer
{
public:
	void OnAttach() override;
	void OnDetach() override;
};