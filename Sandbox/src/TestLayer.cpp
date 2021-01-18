#include "TestLayer.h"


void TestLayer::OnAttach()
{
	RUC_INFO("Client info test {}", 42);
	RUC_TRACE("Client trace test {}", 42);
	RUC_WARN("Client warning test {}", 42);
	RUC_ERROR("Client error test {}", 42);
}

void TestLayer::OnDetach()
{
}

void TestLayer::OnUpdate()
{
	
}
