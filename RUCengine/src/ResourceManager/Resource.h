#pragma once

#include "Base.h"

#include <string>
#include <memory>

namespace RUC
{
	class Resource
	{
	public:
		virtual ~Resource();
		std::string GetName() const { return m_Name; }
	protected:
		Resource(const std::string& name);
		Resource();
	private:
		std::string m_Name;

		template<typename T>
		friend class ResPtr;
	};
}