#pragma once

#include "Core/Application.h"
#include "Layers/LayerStack.h"

int main(int argc, char** argv)
{
	auto app = new RUC::Application(RUC::GetAppName());

	RUC::LayerStack* layerStack = new RUC::LayerStack();
	RUC::RegisterLayers(layerStack);
	app->SetLayers(layerStack);
	
	app->Run();

	//Detach layers before shutting down the app
	delete layerStack;
	delete app;
}