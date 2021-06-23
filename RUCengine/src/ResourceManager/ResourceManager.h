#pragma once

#include "Resource.h"
#include "ResPtr.h"

#include <unordered_map>
#include <memory>

namespace RUC
{

	struct ResourceMetadata
	{
		Resource* ResPtr;
		int RefCount;
		int NextFreePos;

		ResourceMetadata(Resource* resPtr)
		{
			ResPtr = resPtr;
			RefCount = 0;
			NextFreePos = -1;
		}
	};

	class ResourceManager
	{
	public:

		template<typename T>
		static ResPtr<T> GetByName(const std::string& name)
		{
			auto pos = s_Indices.find(name);

			if (pos == s_Indices.end())
			{
				RUC_WARN("Resource {0} not found. Nullptr returned", name);
				return ResPtr<T>();
			}
			auto ptr = (T*)s_Metadata[s_Indices[name]].ResPtr;
			return ResPtr<T>(ptr, s_Indices[name]);
		}

		static bool Contains(const std::string& name)
		{
			return s_Indices.find(name) != s_Indices.end();
		}

		template<typename T>
		static ResPtr<T> GetFromFile(const std::string& path)
		{
			if (!Contains(path))
			{
				new T(path);
			}
			return GetByName<T>(path);
		}

	private:
		template<typename T>
		static void AddResource(T* resource, const std::string& name)
		{
			if (s_FirstFreePosition == -1)
			{
				s_Metadata.push_back(ResourceMetadata(resource));
				s_Indices[name] = (int)s_Metadata.size() - 1;
			}
			else
			{
				s_Indices[name] = s_FirstFreePosition;
				int next = s_Metadata[s_FirstFreePosition].NextFreePos;
				s_Metadata[s_FirstFreePosition] = ResourceMetadata(resource);
				s_FirstFreePosition = next;
			}
			
		}

		static void DeleteResource(int index);

	private:
		//Index of a resource (by name) on the metadata list
		static std::unordered_map<std::string, int> s_Indices;
		static std::vector<ResourceMetadata> s_Metadata;

		static int s_FirstFreePosition;


		friend class Resource;
		template <typename T>
		friend class ResPtr;
	};
	/*class ResourceManager
	{
	public:

		template<typename T>
		//Returns the element if it exists and loads it from file if it doesn't
		static std::shared_ptr<T> GetFromFile(const std::string& fileName)
		{
			
			auto pos = s_Resources.find(fileName);

			if (pos == s_Resources.end())
			{
				std::shared_ptr<T> Tptr;
				Tptr.reset(T::LoadFromFile(fileName));
				std::shared_ptr<Resource> resPtr = std::dynamic_pointer_cast<Resource>(Tptr);
				s_Resources[fileName] = resPtr;
				return Tptr;
			}
			else
			{
				return std::dynamic_pointer_cast<T>(s_Resources[fileName].lock());
			}
		}

		template<typename T>
		static std::shared_ptr<T> GetByName(const std::string& name)
		{
			auto pos = s_Resources.find(name);

			if (pos == s_Resources.end())
			{
				return std::shared_ptr<T>();
			}
			return std::dynamic_pointer_cast<T>(s_Resources[name].lock());
		}
		
		//TODO: create persistent resources (always loaded)
		template<typename T, typename... Args>
		static ResPtr<T> Create(const std::string& name, Args... args)
		{
			auto pos = s_Resources.find(name);
			if (pos != s_Resources.end())
			{
				RUC_WARN("Can't add resource {0}: it already exists", name);
			//	return ResPtr<T>::Cast(s_Resources2[name]);
			}

			ResPtr<Resource> test =  ResPtr<Resource>(T::Create(name, args...));
			s_Resources2[name] = test;
			return ResPtr<T>::Cast(s_Resources2[name]);
		}

		template<typename T>
		static std::weak_ptr<T> GetByNameWeak(const std::string& name)
		{
			auto pos = s_Resources.find(name);

			if (pos == s_Resources.end())
			{
				return std::weak_ptr<T>();
			}
			return std::dynamic_pointer_cast<T>(s_Resources[name]);
		}

		template<>
		static std::weak_ptr<Resource> GetByNameWeak(const std::string& name)
		{
			auto pos = s_Resources.find(name);

			if (pos == s_Resources.end())
			{
				return std::weak_ptr<Resource>();
			}
			return s_Resources[name];
		}

	private:
		static void Unload(const std::string& name);

	private:
		static std::unordered_map <std::string, std::weak_ptr<Resource>> s_Resources;
		static std::unordered_map <std::string, ResPtr<Resource>> s_Resources2;

		friend class Resource;
	};*/
}