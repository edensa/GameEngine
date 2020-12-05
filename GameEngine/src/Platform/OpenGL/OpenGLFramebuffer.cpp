#include "ngpch.h"
#include "OpenGLFramebuffer.h"

#include <glad/glad.h>

namespace engine
{
	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& spec)
		: m_Specification(spec)
	{
		Invalidate();
	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		glDeleteTextures(1, &m_ColorAttachment);
		glDeleteFramebuffers(1, &m_RenderID);
	}

	void OpenGLFramebuffer::Invalidate()
	{
		glCreateFramebuffers(1, &m_RenderID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_RenderID);
		
		glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachment);
		glTextureStorage2D(m_ColorAttachment, 1, GL_RGBA8, m_Specification.width, m_Specification.height);

		glTextureParameteri(m_ColorAttachment, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_ColorAttachment, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);

		glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthAttachment);
		glTextureStorage2D(m_DepthAttachment, 1, GL_DEPTH24_STENCIL8, m_Specification.width, m_Specification.height);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachment, 0);

		ENGINE_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	const FramebufferSpecification& OpenGLFramebuffer::GetSpecification() const
	{
		return m_Specification;
	}

	void OpenGLFramebuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RenderID);
	}

	void OpenGLFramebuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	uint32_t OpenGLFramebuffer::GetColorAttachmentRendererID() const
	{
		return m_ColorAttachment;
	}
}
