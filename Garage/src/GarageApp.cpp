#include "EditorLayer.h"

namespace engine
{
	
	class GarageApp : public Application
	{
	public:
		GarageApp(ApplicationCommandLineArgs args)
			: Application("Garage Editor", args)
		{
			PushLayer(new EditorLayer());
		}

		virtual ~GarageApp()
		{
		}

	};

	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		return new GarageApp(args);
	}
	
}

#include "Engine/Core/EntryPoint.h"
