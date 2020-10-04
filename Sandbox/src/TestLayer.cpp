#include "TestLayer.h"

#include <iostream>

void TestLayer::OnAttach()
{
}

void TestLayer::OnDetach()
{
}

void TestLayer::OnUpdate()
{
	std::cout << "I'm a test layer" << std::endl;
}
