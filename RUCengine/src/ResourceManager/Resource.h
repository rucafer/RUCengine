#pragma once

#include "Base.h"

#include <string>
#include <memory>

namespace RUC
{
	enum class ResourceFlags : char
	{
		PERSISTENT = 1	//Resource won't be deleted automatically when it has no active ResPtrs
	};

	class Resource
	{
	public:
		virtual ~Resource();
		std::string GetName() const { return m_Name; }
	protected:
		Resource(const std::string& name, char flags = 0);
		Resource();

	private:
		std::string m_Name;
		char m_Flags;

		template<typename T>
		friend class ResPtr;
	};
}