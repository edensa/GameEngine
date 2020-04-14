#include "Sandbox2D.h"

class Sandbox : public engine::Application
{
public:
	Sandbox()
		: Application()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	virtual ~Sandbox()
	{
	}

};

engine::Application* engine::CreateApplication()
{
	return new Sandbox();
}