#pragma once

#include "Resource.h"

#include <unordered_map>
#include <memory>

namespace RUC
{
	class ResourceManager
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
		static std::shared_ptr<T> Create(const std::string& name, Args... args)
		{
			auto pos = s_Resources.find(name);
			if (pos != s_Resources.end())
			{
				RUC_WARN("Can't add resource {0}: it already exists", name);
				return std::dynamic_pointer_cast<T>(s_Resources[name].lock());
			}

			std::shared_ptr<T> Tptr;
			Tptr.reset(T::Create(name, args...));
			std::shared_ptr<Resource> resPtr = std::dynamic_pointer_cast<Resource>(Tptr);
			s_Resources[name] = resPtr;
			return Tptr;
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

		friend class Resource;
	};
}