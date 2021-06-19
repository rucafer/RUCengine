#include "Resource.h"
#include "ResourceManager.h"

namespace RUC
{
	Resource::Resource(const std::string& name)
		:m_Name(name)
	{
		ResourceManager::AddResource(this, name);
	}

	Resource::Resource()
	{
		RUC_ASSERT(false, "Resource name must be passed to Resource constructor by the derived resource constructor");
	}

	Resource::~Resource()
	{
		//ResourceManager::Unload(m_Name);
	}
}
