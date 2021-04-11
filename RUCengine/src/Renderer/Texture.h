#pragma once

#include "ResourceManager/Resource.h"

#include <string>

namespace RUC
{
	class Texture : virtual public Resource
	{
	public:
		virtual ~Texture() = default;

		virtual uint32_t getWidth() const = 0;
		virtual uint32_t getHeight() const = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;
	};

	class Texture2D : virtual public Texture
	{
	public:
		static Texture2D* LoadFromFile(const std::string& path);

		static Texture2D* Create(const std::string& name, uint32_t width, uint32_t height, unsigned char* data, size_t size);
	};
}