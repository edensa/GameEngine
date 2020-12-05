#include "ngpch.h"
#include "Framebuffer.h"

#include "Engine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace engine
{
	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			ENGINE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLFramebuffer>(spec);
		default:
			ENGINE_CORE_ASSERT(false, "unknown RendererAPI!");
			return nullptr;
		}
	}
}
