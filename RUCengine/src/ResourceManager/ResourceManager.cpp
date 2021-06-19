#include "ResourceManager.h"

#include "Base.h"

namespace RUC
{
	std::unordered_map<std::string, int> ResourceManager::s_Indices;
	std::vector<ResourceMetadata> ResourceManager::s_Metadata;

	int ResourceManager::s_FirstFreePosition = -1;


	void ResourceManager::DeleteResource(int index)
	{	
		ResourceMetadata metadata = s_Metadata[index];

		//Delete from hashmap
		s_Indices.erase(s_Indices.find(metadata.ResPtr->GetName()));

		//Delete from vector
		if (s_FirstFreePosition == -1)
		{
			s_FirstFreePosition = index;
		}
		else
		{
			int nextFree = s_FirstFreePosition;
			while (s_Metadata[nextFree].NextFreePos != -1)
			{
				nextFree = s_Metadata[nextFree].NextFreePos;
			}

			s_Metadata[nextFree].NextFreePos = index;
		}

		//Destroy resource
		delete s_Metadata[index].ResPtr;
		s_Metadata[index].ResPtr = nullptr;
	}

	/*
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
	}*/
}