#pragma once

#include "RenderCommand.h"

namespace engine
{

	class Renderer
	{
	public:

		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

		static void Submit();


		static inline RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	};

}