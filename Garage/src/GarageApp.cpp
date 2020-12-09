#include "EditorLayer.h"


class GarageApp : public engine::Application
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

engine::Application* engine::CreateApplication()
{
	return new GarageApp();
}

#include "Engine/Core/EntryPoint.h"