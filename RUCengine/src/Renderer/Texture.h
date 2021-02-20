#pragma once

#include <string>

namespace RUC
{
	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual uint32_t getWidth() const = 0;
		virtual uint32_t getHeight() const = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		static Texture2D* Create(const std::string& path);
		static Texture2D* Create(uint32_t id, uint32_t width, uint32_t height);
	};
}