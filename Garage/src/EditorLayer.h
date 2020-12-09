#pragma once

#include "Engine.h"

class EditorLayer : public engine::Layer
{
public:
	EditorLayer();
	virtual ~EditorLayer() = default;
	
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	
	virtual void OnUpdate(engine::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(engine::Event& e) override;

private:
	engine::OrthographicCameraController m_CameraController;

	// Temp
	engine::Ref<engine::VertexArray> m_SquareVA;
	engine::Ref<engine::Shader> m_FlatColorShader;
	engine::Ref<engine::Framebuffer> m_Framebuffer;
	
	engine::Ref<engine::Texture2D> m_CheckerboardTexture;

	glm::uvec2 m_ViewportPanelSize = {0, 0};

	struct ProfileResult
	{
		const char* Name;
		float Time;
	};

	std::vector<ProfileResult> m_ProfileResults;
	
	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};