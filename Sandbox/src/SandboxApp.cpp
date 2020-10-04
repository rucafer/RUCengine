#include "Core/Application.h"
#include "Core/EntryPoint.h"

#include "TestLayer.h"

const char* RUC::GetAppName()
{
	return "Sandbox";
}

void RUC::RegisterLayers(LayerStack* layerStack)
{
	TestLayer* test = new TestLayer();
	layerStack->Push(test);
}