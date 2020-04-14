#include "ExampleLayer.h"

#include <imgui.h>

ExampleLayer::ExampleLayer(): Layer("Example")
                              , m_CameraController(1280.0f / 720.0f)
{
	m_VertexArray = engine::VertexArray::Create();

	float verticies[7 * 3] = {
		-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
		0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
		0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f,
	};

	engine::Ref<engine::VertexBuffer> vertexBuffer = engine::VertexBuffer::Create(verticies, sizeof(verticies));

	{
		engine::BufferLayout layout = {
			{engine::ShaderDataType::Float3, "a_Position"},
			{engine::ShaderDataType::Float4, "a_Color"}
		};
		vertexBuffer->SetLayout(layout);
	}

	m_VertexArray->AddVertexBuffer(vertexBuffer);

	unsigned indicies[3] = {
		0, 1, 2
	};

	engine::Ref<engine::IndexBuffer> indexBuffer = engine::IndexBuffer::Create(
		indicies, sizeof(indicies) / sizeof(uint32_t));

	m_VertexArray->SetIndexBuffer(indexBuffer);

	m_SquareVA = engine::VertexArray::Create();

	float squareVerticies[5 * 4] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	};

	engine::Ref<engine::VertexBuffer> squareVB = engine::VertexBuffer::Create(squareVerticies, sizeof(squareVerticies));

	squareVB->SetLayout({
		{engine::ShaderDataType::Float3, "a_Position"},
		{engine::ShaderDataType::Float2, "a_TexCoord"}
	});
	m_SquareVA->AddVertexBuffer(squareVB);

	unsigned squareIndicies[6] = {
		0, 1, 2, 2, 3, 0
	};

	engine::Ref<engine::IndexBuffer> squareIB = engine::IndexBuffer::Create(
		squareIndicies, sizeof(squareIndicies) / sizeof(uint32_t));

	m_SquareVA->SetIndexBuffer(squareIB);

	std::string vertexSrc =
		R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";
	std::string fragmentSrc =
		R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = v_Color;
			}
		)";

	m_Shader = engine::Shader::Create("VertexColorTriangle", vertexSrc, fragmentSrc);

	std::string flatColorVertexSrc =
		R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";
	std::string flatColorFragmentSrc =
		R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

	m_FlatColorShader = engine::Shader::Create("FlatColor", flatColorVertexSrc, flatColorFragmentSrc);

	auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

	m_Texture = engine::Texture2D::Create("assets/textures/Checkerboard.png");
	m_ChernoLogoTexture = engine::Texture2D::Create("assets/textures/ChernoLogo.png");

	textureShader->Bind();
	textureShader->SetInt("u_Texture", 0);
}

void ExampleLayer::OnUpdate(engine::Timestep ts)
{
	// Update
	m_CameraController.OnUpdate(ts);

	if (engine::Input::IsKeyPressed(ENGINE_KEY_J))
		m_SquarePosition.x -= m_SquareMoveSpeed * ts;

	else if (engine::Input::IsKeyPressed(ENGINE_KEY_L))
		m_SquarePosition.x += m_SquareMoveSpeed * ts;

	if (engine::Input::IsKeyPressed(ENGINE_KEY_I))
		m_SquarePosition.y += m_SquareMoveSpeed * ts;

	else if (engine::Input::IsKeyPressed(ENGINE_KEY_K))
		m_SquarePosition.y -= m_SquareMoveSpeed * ts;

	// Render
	engine::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
	engine::RenderCommand::Clear();

	engine::Renderer::BeginScene(m_CameraController.GetCamera());

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

	m_FlatColorShader->Bind();
	m_FlatColorShader->SetFloat3("u_Color", m_SquareColor);

	for (int i = 0; i < 20; ++i)
	{
		for (int j = 0; j < 20; ++j)
		{
			glm::vec3 pos(i * 0.11f, j * 0.11f, 0.0f);
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;

			engine::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
		}
	}

	auto textureShader = m_ShaderLibrary.Get("Texture");

	m_Texture->Bind();
	engine::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
	m_ChernoLogoTexture->Bind();
	engine::Renderer::Submit(textureShader, m_SquareVA,
	                         glm::translate(glm::mat4(1.0f), glm::vec3(0.25f, -0.25f, 0.0f)) * glm::scale(
		                         glm::mat4(1.0f), glm::vec3(1.5f)));

	// Triangle
	// engine::Renderer::Submit(m_Shader, m_VertexArray);

	engine::Renderer::EndScene();
}

void ExampleLayer::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void ExampleLayer::OnEvent(engine::Event& e)
{
	m_CameraController.OnEvent(e);
}
