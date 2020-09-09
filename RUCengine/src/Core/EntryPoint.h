/*
	Entry point of the engine
	This file must be included by the client, who must define the CreateApp funtion
*/

#pragma once

#include "Application.h"
#include "Log/Log.h"

extern RUC::Application* RUC::CreateApp();

int main(int argc, char** argv)
{
	//Initialize logger
	RUC::Log::Init();

	auto app = RUC::CreateApp();
	app->Run();
	delete app;
	return 0;
}