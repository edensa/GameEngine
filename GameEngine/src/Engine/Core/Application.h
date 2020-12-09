#pragma once

#include "Engine/Core/Base.h"
#include "Engine/Core/Window.h"
#include "Engine/Core/LayerStack.h"
#include "Engine/Events/Event.h"
#include "Engine/Events/ApplicationEvent.h"

#include "Engine/Core/Timestep.h"

#include "Engine/ImGui/ImGuiLayer.h"

int main(int argc, char** argv);

namespace engine {

	class Application
	{
	public:
		Application(const std::string& name = "Game Engine");
		virtual ~Application();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		Window& GetWindow() { return *m_Window; }
		
		void Close();

		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }
		
		static Application& Get() { return *s_Instance; }
	private:
		void Run();
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Minimized = false;
		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime;

		static Application* s_Instance;
		friend int ::main(int argc, char** argv);
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}
