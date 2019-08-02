#pragma once

#include "Engine/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace engine
{
	
	class OpenGLContext : public GraphicsContext
	{
	public:
		explicit OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_WindowHandle;
	};

}