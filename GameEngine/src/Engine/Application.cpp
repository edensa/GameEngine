#include "Application.h"

#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Log.h"

namespace engine {

	Application::Application()
	{
	}


	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			ENGINE_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			ENGINE_TRACE(e);
		}

		while (true);
	}

}