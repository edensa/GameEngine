#pragma once

#include "Engine.h"

class Sandbox2D : public engine::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;
	
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	
	virtual void OnUpdate(engine::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(engine::Event& e) override;

private:
	// Temp
	engine::ShaderLibrary m_ShaderLibrary;
	engine::Ref<engine::VertexArray> m_SquareVA;
	engine::Ref<engine::Shader> m_FlatColorShader;
	engine::OrthographicCameraController m_CameraController;
	
	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};