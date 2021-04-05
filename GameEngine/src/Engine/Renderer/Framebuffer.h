#pragma once

#include "Engine/Core/Base.h"

namespace engine
{

	enum class FramebufferTextureFormat
	{
		None = 0,

		// Color
		RGBA8,

		// Depth/stencil
		DEPTH32STENCIL8,

		// Defaults
		Depth = DEPTH32STENCIL8
	};

	struct FramebufferTextureSpecification
	{
		FramebufferTextureSpecification() = default;
		FramebufferTextureSpecification(FramebufferTextureFormat format)
			: TextureFormat(format) {}

		FramebufferTextureFormat TextureFormat = FramebufferTextureFormat::None;
		// TODO: filtering/wrap
	};

	struct FramebufferAttachmentSpecification
	{
		FramebufferAttachmentSpecification() = default;
		FramebufferAttachmentSpecification(const std::initializer_list<FramebufferTextureSpecification> attachments)
			: Attachments(attachments) {}
		
		std::vector<FramebufferTextureSpecification> Attachments;
	};
	
	struct FramebufferSpecification
	{
		uint32_t width = 0, height = 0;
		uint32_t samples = 1;

		FramebufferAttachmentSpecification TextureSpecification;
		bool SwapChainTarget = false;
	};
	
	class Framebuffer
	{
	public:
		virtual ~Framebuffer() = default;
		
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void Resize(uint32_t width, uint32_t height) = 0;

		virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const = 0;
	public:
		virtual const FramebufferSpecification& GetSpecification() const = 0;
		
		static Ref<Framebuffer> Create(const FramebufferSpecification& spec);
		
	};
	
}
