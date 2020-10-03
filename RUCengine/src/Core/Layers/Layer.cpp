#include "Layer.h"

#include <iostream>

namespace RUC
{
	Layer::Layer(const std::string& name)
		:m_Name(name)
	{

	}

	void Layer::OnAttach()
	{

	}

	void Layer::OnDetach()
	{

	}

	void Layer::OnUpdate()
	{
		std::cout << m_Name << std::endl;
	}
}