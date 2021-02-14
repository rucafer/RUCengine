#pragma once

#include "Renderer.h"
#include "Texture.h"
#include "Shader.h"

namespace RUC
{
	class Renderer2D
	{
	public:
		
		static void Init();

		static void DrawQuad(const glm::vec3& position, const glm::vec3& scale, const std::shared_ptr<Shader>& shader, const std::shared_ptr<Texture>& texture);
	};
}