#include "ngpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace engine
{
	
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
	
}
