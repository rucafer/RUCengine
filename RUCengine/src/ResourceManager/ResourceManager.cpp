#include "ResourceManager.h"

#include "Base.h"

namespace RUC
{
	std::unordered_map <std::string, std::weak_ptr<Resource>> ResourceManager::s_Resources;

	void ResourceManager::Unload(const std::string& name)
	{
		auto pos = s_Resources.find(name);
		if (pos != s_Resources.end())
		{
			if (s_Resources[name].expired())
			{
				s_Resources.erase(pos);
			}
			else
			{
				RUC_ASSERT(false, "Failed to unload resource {0}: it is being used", name);
			}
		}
	}
}