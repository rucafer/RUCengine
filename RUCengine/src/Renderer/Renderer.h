#pragma once

#include "RenderDevice.h"
#include "RenderCommand.h"

#include "VertexArray.h"

namespace RUC
{
	class Renderer
	{
	public:
		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

		static void Init();

		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);
	};
}