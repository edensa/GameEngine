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

		virtual void Resize(uint32_t width, uint32_t height) override;
		virtual int ReadPixel(uint32_t index, int x, int y) override;

		virtual void ClearAttachment(uint32_t index, int value) override;

		virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const override;
		
	private:
		uint32_t m_RenderID = 0;
		FramebufferSpecification m_Specification;

		std::vector<FramebufferTextureSpecification> m_ColorAttachmentSpecifications;
		FramebufferTextureSpecification m_DepthAttachmentSpecification;

		std::vector<uint32_t> m_ColorAttachments;
		uint32_t m_DepthAttachment = 0;
	};

}
