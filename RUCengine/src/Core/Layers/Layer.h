#pragma once

#include "Base.h"

#include <string>

namespace RUC
{

	class Layer
	{
	public:
		Layer() = default;
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}

		virtual void OnUpdate() {}
		virtual void OnImGuiRender() {}
	};

}