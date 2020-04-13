#include "ngpch.h"
#include "Engine/Renderer/RenderCommand.h"

namespace engine
{
	
	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
	
}
