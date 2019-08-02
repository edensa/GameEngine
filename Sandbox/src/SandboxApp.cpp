#include <Engine.h>

#include <imgui.h>

class ExampleLayer : public engine::Layer
{
public:
	ExampleLayer()
	{
		
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnUpdate() override
	{
		//ENGINE_INFO("ExampleLayer::Update");

		if (engine::Input::IsKeyPressed(ENGINE_KEY_TAB))
			ENGINE_INFO("Tab key is pressed!");


	}

	void OnEvent(engine::Event& event) override
	{
		//ENGINE_TRACE("{0}", event);
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