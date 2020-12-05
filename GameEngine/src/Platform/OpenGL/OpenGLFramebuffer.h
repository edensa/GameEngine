#pragma once

#include "Engine/Renderer/Framebuffer.h"

namespace engine
{

	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSpecification& spec);
		virtual ~OpenGLFramebuffer();

		void Invalidate();

		const FramebufferSpecification& GetSpecification() const override;

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual uint32_t GetColorAttachmentRendererID() const override;
		
	private:
		uint32_t m_RenderID;
		uint32_t m_ColorAttachment, m_DepthAttachment;
		FramebufferSpecification m_Specification;
	};

}
