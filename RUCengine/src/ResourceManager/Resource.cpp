#include "Resource.h"
#include "ResourceManager.h"

namespace RUC
{
	Resource::Resource(const std::string& name)
		:m_Name(name)
	{
	}

	Resource::~Resource()
	{
		ResourceManager::Unload(m_Name);
	}
}
