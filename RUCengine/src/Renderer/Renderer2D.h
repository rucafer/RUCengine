#pragma once

#include "Renderer.h"
#include "Texture.h"
#include "Shader.h"
#include "Material.h"

namespace RUC
{
	class Renderer2D
	{
	public:
		
		static void Init();

		static void DrawQuad(const glm::vec3& position, const glm::vec3& scale, ResPtr<Shader> shader, ResPtr<Texture> texture);
		static void DrawQuad(const glm::vec3& position, const glm::vec3& scale, ResPtr<Material> material);
	};
}