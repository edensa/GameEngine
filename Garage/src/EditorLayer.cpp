#include "EditorLayer.h"
#include <imgui.h>

#include "glm/gtc/type_ptr.hpp"

#include <chrono>

EditorLayer::EditorLayer()
	: Layer("EditorLayer")
	, m_CameraController(1280.0f / 720.0f)
{
	ENGINE_PROFILE_FUNCTION();
}

void EditorLayer::OnAttach()
{
	ENGINE_PROFILE_FUNCTION();

	m_CheckerboardTexture = engine::Texture2D::Create("assets/textures/Checkerboard.png");

	engine::FramebufferSpecification fbSpec;
	fbSpec.width = 1280;
	fbSpec.height = 720;
	m_Framebuffer = engine::Framebuffer::Create(fbSpec);
}

void EditorLayer::OnDetach()
{
}

void EditorLayer::OnUpdate(engine::Timestep ts)
{
	ENGINE_PROFILE_FUNCTION();
	
	// Update
	{
		ENGINE_PROFILE_SCOPE("CameraController::OnUpdate");

		m_CameraController.OnUpdate(ts);
	}

	// Render
	{
		ENGINE_PROFILE_SCOPE("Renderer Prep");
		m_Framebuffer->Bind();
		engine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		engine::RenderCommand::Clear();
	}

	engine::Renderer2D::ResetStats();
	{
		static float rotation = 0.0f;
		rotation += ts * 50.0f;

		
		ENGINE_PROFILE_SCOPE("Renderer Draw");
		engine::Renderer2D::BeginScene(m_CameraController.GetCamera());

		engine::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f }, { 1.0f, 1.0f }, rotation, { 0.8f, 0.2f, 0.3f, 1.0f });
		engine::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		engine::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, m_SquareColor);
		engine::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_CheckerboardTexture, 10.0f);
		engine::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, rotation, m_CheckerboardTexture, 20.0f );
		engine::Renderer2D::EndScene();

		engine::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for (float y = -5.0; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0; x < 5.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 5.0f) / 10.f, 0.4f, (y + 5.0f) / 10.f, 0.7f };
				engine::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
			}
		}
		engine::Renderer2D::EndScene();
		m_Framebuffer->Unbind();
	}
}

void EditorLayer::OnImGuiRender()
{
	ENGINE_PROFILE_FUNCTION();

	static bool dockingEnabled = true;
	if (dockingEnabled)
	{
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
	}
	
	ImGui::Begin("Settings");

	auto stats = engine::Renderer2D::GetStats();
	
	ImGui::Text("Renderer2D Stats: ");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
	
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

	uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
	ImGui::Image((void*)textureID, ImVec2{1280.0f, 720.0f}, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
	
	ImGui::End();
}

void EditorLayer::OnEvent(engine::Event& e)
{
	m_CameraController.OnEvent(e);
}
