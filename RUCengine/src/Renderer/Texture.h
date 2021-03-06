#pragma once

#include "ResourceManager/Resource.h"

#include <string>

namespace RUC
{
	class Texture : public Resource
	{
	public:
		virtual ~Texture() = default;

		virtual uint32_t getWidth() const = 0;
		virtual uint32_t getHeight() const = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;

	protected:
		Texture(const std::string name, char flags)
			:Resource(name, flags)
		{

		}
	};

	class Texture2D : public Texture
	{
	public:
		static ResPtr<Texture2D> LoadFromFile(const std::string& path);

		static ResPtr<Texture2D> Create(const std::string& name, uint32_t width, uint32_t height, unsigned char* data, size_t size, char flags = 0);
		
	protected:
		Texture2D(const std::string& name, char flags = 0)
			:Texture(name, flags)
		{

		}
	};
}