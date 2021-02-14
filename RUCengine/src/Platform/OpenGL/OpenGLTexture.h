#pragma once

#include "Renderer/Texture.h"

namespace RUC
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& filePath);
		~OpenGLTexture2D();

		uint32_t getWidth() const override { return m_Width; }
		uint32_t getHeight() const override { return m_Height; }

		void Bind(uint32_t slot = 0) const override;

	private:
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;
	};
}