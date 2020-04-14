#include "ngpch.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

#include <glad/glad.h>

namespace engine
{
	OpenGLVertexBuffer::OpenGLVertexBuffer(float* verticies, uint32_t size)
		: m_RendererID(0)
	{
		ENGINE_PROFILE_FUNCTION();
		
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, verticies, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		ENGINE_PROFILE_FUNCTION();
		
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		ENGINE_PROFILE_FUNCTION();
		
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		ENGINE_PROFILE_FUNCTION();
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indicies, uint32_t count)
		: m_RendererID(0)
		, m_Count(count)
	{
		ENGINE_PROFILE_FUNCTION();
		
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * count, indicies, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		ENGINE_PROFILE_FUNCTION();
		
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		ENGINE_PROFILE_FUNCTION();
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		ENGINE_PROFILE_FUNCTION();
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
