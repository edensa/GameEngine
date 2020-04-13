#include "Sandbox2D.h"
#include <imgui.h>

#include "glm/gtc/type_ptr.hpp"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D")
	, m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
	m_CheckerboardTexture = engine::Texture2D::Create("assets/textures/Checkerboard.png");
	m_ChernoLogoTexture = engine::Texture2D::Create("assets/textures/ChernoLogo.png");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(engine::Timestep ts)
{
	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	engine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	engine::RenderCommand::Clear();

	engine::Renderer2D::BeginScene(m_CameraController.GetCamera());

	engine::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	engine::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
	engine::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture);
	engine::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(engine::Event& e)
{
	m_CameraController.OnEvent(e);
}
