#pragma once

#include "RenderDevice.h"
#include "RenderCommand.h"

#include "VertexArray.h"

namespace RUC
{
	class Renderer
	{
	public:
		static RenderDevice::API GetAPI() { return RenderDevice::GetAPI(); }

		static void Init();

		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);
	};
}