#pragma once

#include "Engine.h"
#include "Engine/Core/EntryPoint.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Engine/Renderer/OrthographicCameraController.h"
#include "glm/gtc/type_ptr.inl"

#include "Engine/Renderer/Shader.h"

class ExampleLayer : public engine::Layer
{
public:
	ExampleLayer();

	virtual void OnUpdate(engine::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(engine::Event& e) override;

private:
	engine::ShaderLibrary m_ShaderLibrary;
	engine::Ref<engine::Shader> m_Shader;
	engine::Ref<engine::Shader> m_FlatColorShader;
	//engine::Ref<engine::Shader> m_TextureShader;
	engine::Ref<engine::VertexArray> m_VertexArray;
	engine::Ref<engine::VertexArray> m_SquareVA;

	engine::Ref<engine::Texture2D> m_Texture;
	engine::Ref<engine::Texture2D> m_ChernoLogoTexture;

	engine::OrthographicCameraController m_CameraController;

	float m_SquareMoveSpeed = 1.0f;
	glm::vec3 m_SquarePosition = glm::vec3(0.0f);

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};
