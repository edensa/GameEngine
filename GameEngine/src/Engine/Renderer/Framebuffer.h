#pragma once

#include "Engine/Core/Base.h"

namespace engine
{

	struct FramebufferSpecification
	{
		uint32_t width, height;
		uint32_t samples = 1;

		bool SwapChainTarget = false;
	};
	
	class Framebuffer
	{
	public:
		virtual ~Framebuffer() = default;
		
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual uint32_t GetColorAttachmentRendererID()	const = 0;
	public:
		virtual const FramebufferSpecification& GetSpecification() const = 0;
		
		static Ref<Framebuffer> Create(const FramebufferSpecification& spec);
		
	};
	
}