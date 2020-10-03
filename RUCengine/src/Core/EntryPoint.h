#pragma once

#include "Core/Application.h"

int main(int argc, char** argv)
{
	auto app = new RUC::Application(RUC::GetAppName());
	app->Run();
	delete app;
}