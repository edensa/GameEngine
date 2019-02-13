#include <Engine.h>


class ExampleLayer : public engine::Layer
{
public:
	ExampleLayer()
	{
	}

	void OnUpdate() override
	{
		ENGINE_INFO("ExampleLayer::Update");
	}

	void OnEvent(engine::Event& event) override
	{
		ENGINE_TRACE("{0}", event);
	}
};

class Sandbox : public engine::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	virtual ~Sandbox()
	{
	}

};

engine::Application* engine::CreateApplication()
{
	return new Sandbox();
}