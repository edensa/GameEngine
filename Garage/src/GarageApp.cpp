#include "EditorLayer.h"

namespace engine
{
	
	class GarageApp : public Application
	{
	public:
		GarageApp()
			: Application("Garage Editor")
		{
			PushLayer(new EditorLayer());
		}

		virtual ~GarageApp()
		{
		}

	};

	Application* CreateApplication()
	{
		return new GarageApp();
	}
	
}

#include "Engine/Core/EntryPoint.h"
