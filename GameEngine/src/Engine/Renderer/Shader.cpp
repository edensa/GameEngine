#include "ngpch.h"
#include "Shader.h"

#include <glad/glad.h>
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace engine
{
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			ENGINE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLShader(vertexSrc, fragmentSrc);
		default:
			ENGINE_CORE_ASSERT(false, "unknown RendererAPI!");
			return nullptr;
		}
	}

}
