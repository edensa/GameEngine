#include "ngpch.h"
#include "Platform/OpenGL/OpenGLContext.h"

#include <GLFW/glfw3.h>
#include "glad/glad.h"

namespace engine
{

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		ENGINE_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		ENGINE_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ENGINE_CORE_ASSERT(status, "Failed to initialize Glad!")

		ENGINE_CORE_INFO("OpenGL Renderer:");
		ENGINE_CORE_INFO("	Vendor: {0}", glGetString(GL_VENDOR));
		ENGINE_CORE_INFO("	Renderer: {0}", glGetString(GL_RENDERER));
		ENGINE_CORE_INFO("	Version: {0}", glGetString(GL_VERSION));

		ENGINE_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "Engine requires at least OpenGL version 4.5!");

		int texture_units;
		glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &texture_units);
		ENGINE_CORE_INFO("  texture_units: {0}", texture_units);
	}

	void OpenGLContext::SwapBuffers()
	{
		ENGINE_PROFILE_FUNCTION();
		glfwSwapBuffers(m_WindowHandle);
	}

}
