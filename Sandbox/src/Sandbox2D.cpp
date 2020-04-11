#include "Sandbox2D.h"
#include "imgui.h"

#include "glm/gtc/type_ptr.hpp"
#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D")
	, m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
	m_SquareVA = engine::VertexArray::Create();

	float squareVerticies[3 * 4] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f,
	};

	engine::Ref<engine::VertexBuffer> squareVB;
	squareVB.reset(engine::VertexBuffer::Create(squareVerticies, sizeof(squareVerticies)));

	squareVB->SetLayout({
		{ engine::ShaderDataType::Float3, "a_Position" },
	});
	m_SquareVA->AddVertexBuffer(squareVB);

	unsigned squareIndicies[6] = { 0, 1, 2, 2, 3, 0 };
	engine::Ref<engine::IndexBuffer> squareIB;
	squareIB.reset(engine::IndexBuffer::Create(squareIndicies, sizeof(squareIndicies) / sizeof(uint32_t)));
	m_SquareVA->SetIndexBuffer(squareIB);

	//m_FlatColorShader = m_ShaderLibrary.Load("assets/shaders/FlatColorShader.glsl");
	m_FlatColorShader = m_ShaderLibrary.Load("assets/shaders/FlatColorShader.glsl");
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

	engine::Renderer::BeginScene(m_CameraController.GetCamera());

	auto glShader = std::dynamic_pointer_cast<engine::OpenGLShader>(m_FlatColorShader);
	glShader->Bind();
	glShader->UploadUniformFloat4("u_Color", m_SquareColor);

	engine::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	engine::Renderer::EndScene();
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
