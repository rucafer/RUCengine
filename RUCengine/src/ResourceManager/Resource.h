#pragma once

#include "Base.h"

#include <string>
#include <memory>

namespace RUC
{
	class Resource
	{
	public:
		Resource(const std::string& name);
		Resource() = default;
		virtual ~Resource();
	private:
		std::string m_Name;
	};
}