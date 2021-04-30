#include "ngpch.h"
#include "OpenGLFramebuffer.h"

#include <glad/glad.h>

namespace engine
{

	namespace Utils
	{
		GLenum TextureTarget(bool multi_sampled)
		{
			return multi_sampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
		}
		
		static void CreateTextures(bool multi_sampled, uint32_t* outID, uint32_t count)
		{
			glCreateTextures(TextureTarget(multi_sampled), count, outID);
		}

		static void BindTexture(bool multi_sampled, uint32_t id)
		{
			glBindTexture(TextureTarget(multi_sampled), id);
		}
		
		static void AttachColorTexture(uint32_t id, int samples, GLenum format, uint32_t width, uint32_t height, uint32_t index)
		{
			bool multi_sampled = samples > 1;
			if (multi_sampled)
			{
				glTextureStorage2DMultisample(id, samples, format, width, height, GL_FALSE);
			} else
			{
				glTextureStorage2D(id, 1, format, width, height);
			}

			glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTextureParameteri(id, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glTextureParameteri(id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTextureParameteri(id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, TextureTarget(multi_sampled), id, 0);
		}
		
		static void AttachDepthTexture(uint32_t id, int samples, GLenum format, GLenum attachmentType, uint32_t width, uint32_t height)
		{
			bool multi_sampled = samples > 1;
			if (multi_sampled)
			{
				glTextureStorage2DMultisample(id, samples, format, width, height, GL_FALSE);
			}
			else
			{
				glTextureStorage2D(id, 1, format, width, height);
			}

			glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, TextureTarget(multi_sampled), id, 0);
		}
		
		static bool isDepthFormat(FramebufferTextureFormat format)
		{
			switch (format)
			{
			case FramebufferTextureFormat::DEPTH32STENCIL8: return true;
			default: return false;;
			}
		}
		
	}
	
	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& spec)
		: m_Specification(spec)
	{
		for (auto specs : m_Specification.TextureSpecification.Attachments)
		{
			if (!Utils::isDepthFormat(specs.TextureFormat))
				m_ColorAttachmentSpecifications.emplace_back(specs);
			else
				m_DepthAttachmentSpecification = specs;
		}
		
		Invalidate();
	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		glDeleteFramebuffers(1, &m_RenderID);
		glDeleteTextures(m_ColorAttachments.size(), m_ColorAttachments.data());
		glDeleteTextures(1, &m_DepthAttachment);
	}

	void OpenGLFramebuffer::Invalidate()
	{
		if (m_RenderID)
		{
			glDeleteFramebuffers(1, &m_RenderID);
			glDeleteTextures(m_ColorAttachments.size(), m_ColorAttachments.data());
			glDeleteTextures(1, &m_DepthAttachment);
			m_ColorAttachments.clear();
			m_RenderID = m_DepthAttachment = 0;
		}
		
		glCreateFramebuffers(1, &m_RenderID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_RenderID);

		bool multi_sample = m_Specification.samples > 1;
		
		if (m_ColorAttachmentSpecifications.size())
		{
			m_ColorAttachments.resize(m_ColorAttachmentSpecifications.size());
			Utils::CreateTextures(multi_sample, m_ColorAttachments.data(), m_ColorAttachments.size());

			// Attachments
			for (size_t i = 0; i < m_ColorAttachmentSpecifications.size(); ++i)
			{
				Utils::BindTexture(multi_sample, m_ColorAttachments[i]);
				switch (m_ColorAttachmentSpecifications[i].TextureFormat)
				{
				case FramebufferTextureFormat::RGBA8:
					Utils::AttachColorTexture(m_ColorAttachments[i], m_Specification.samples, GL_RGB8, m_Specification.width, m_Specification.height, i);
					break;
				case FramebufferTextureFormat::RED_INTEGER:
					Utils::AttachColorTexture(m_ColorAttachments[i], m_Specification.samples, GL_R32I, m_Specification.width, m_Specification.height, i);
					break;
				default: ENGINE_CORE_ASSERT(false, "unknown texture format!");
				}
			}
		}

		if (m_DepthAttachmentSpecification.TextureFormat != FramebufferTextureFormat::None)
		{
			Utils::CreateTextures(multi_sample, &m_DepthAttachment, 1);
			Utils::BindTexture(multi_sample, m_DepthAttachment);
			switch (m_DepthAttachmentSpecification.TextureFormat)
			{
			case FramebufferTextureFormat::DEPTH32STENCIL8:
				Utils::AttachDepthTexture(m_DepthAttachment, m_Specification.samples, 
					GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT, m_Specification.width, m_Specification.height);
				break;
			default: ENGINE_CORE_ASSERT(false, "unknown texture format!");
			}
		}

		if (m_ColorAttachments.size() > 1)
		{
			ENGINE_CORE_ASSERT(m_ColorAttachments.size() <= 4, "maximum 4 color attachments are supported");
			GLenum buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
			glDrawBuffers(m_ColorAttachments.size(), buffers);
		} else if (m_ColorAttachments.empty())
		{
			// Only depth-pass
			glDrawBuffer(GL_NONE);
		}
		
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
		glViewport(0, 0, m_Specification.width, m_Specification.height);
	}

	void OpenGLFramebuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFramebuffer::Resize(uint32_t width, uint32_t height)
	{
		m_Specification.width = width;
		m_Specification.height = height;
		Invalidate();
	}
	
	int OpenGLFramebuffer::ReadPixel(uint32_t index, int x, int y)
	{
		ENGINE_CORE_ASSERT(index < m_ColorAttachments.size(), "color attachment index index out of range!");
		glReadBuffer(GL_COLOR_ATTACHMENT0 + index);
		int pixelData;
		glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixelData);
		return pixelData;
	}

	uint32_t OpenGLFramebuffer::GetColorAttachmentRendererID(uint32_t index) const
	{
		ENGINE_CORE_ASSERT(index < m_ColorAttachments.size(), "color attachment index index out of range!");
		return m_ColorAttachments[index];
	}
}
