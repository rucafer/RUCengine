/*
	Entry point of the engine
	This file must be included by the client, who must define the CreateApp funtion
*/

#pragma once

#include "Application.h"

extern RUC::Application* RUC::CreateApp();

int main(int argc, char** argv) 
{
	auto app = RUC::CreateApp();
	app->Run();
	delete app;
}