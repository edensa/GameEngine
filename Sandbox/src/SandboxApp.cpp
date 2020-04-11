#include <Engine.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>

#include "Engine/Renderer/OrthographicCameraController.h"
#include "glm/gtc/type_ptr.inl"

#include "Engine/Renderer/Shader.h"

class ExampleLayer : public engine::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
		, m_CameraController(1280.0f / 720.0f)
	{
		m_VertexArray.reset(engine::VertexArray::Create());

		float verticies[7 * 3] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f,
		};

		engine::Ref<engine::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(engine::VertexBuffer::Create(verticies, sizeof(verticies)));

		{
			engine::BufferLayout layout = {
				{ engine::ShaderDataType::Float3, "a_Position" },
				{ engine::ShaderDataType::Float4, "a_Color" }
			};
			vertexBuffer->SetLayout(layout);
		}

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned indicies[3] = {
			0, 1, 2
		};

		engine::Ref<engine::IndexBuffer> indexBuffer;
		indexBuffer.reset(engine::IndexBuffer::Create(indicies, sizeof(indicies) / sizeof(uint32_t)));

		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(engine::VertexArray::Create());

		float squareVerticies[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
		};

		engine::Ref<engine::VertexBuffer> squareVB;
		squareVB.reset(engine::VertexBuffer::Create(squareVerticies, sizeof(squareVerticies)));

		squareVB->SetLayout({
			{ engine::ShaderDataType::Float3, "a_Position" },
			{ engine::ShaderDataType::Float2, "a_TexCoord" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		unsigned squareIndicies[6] = {
			0, 1, 2, 2, 3, 0
		};

		engine::Ref<engine::IndexBuffer> squareIB;
		squareIB.reset(engine::IndexBuffer::Create(squareIndicies, sizeof(squareIndicies) / sizeof(uint32_t)));

		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
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
		std::string fragmentSrc = R"(
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

		std::string flatColorVertexSrc = R"(
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
		std::string flatColorFragmentSrc = R"(
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
		
		std::dynamic_pointer_cast<engine::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<engine::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(engine::Timestep ts) override
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
		engine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		engine::RenderCommand::Clear();

		engine::Renderer::BeginScene(m_CameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		
		auto glShader = std::dynamic_pointer_cast<engine::OpenGLShader>(m_FlatColorShader);
		glShader->Bind();
		glShader->UploadUniformFloat3("u_Color", m_SquareColor);
		
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
		engine::Renderer::Submit(textureShader, m_SquareVA, glm::translate(glm::mat4(1.0f), glm::vec3(0.25f, -0.25f, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		
		// Triangle
		// engine::Renderer::Submit(m_Shader, m_VertexArray);

		engine::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(engine::Event& e) override
	{
		m_CameraController.OnEvent(e);
	}

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
	
	glm::vec3 m_SquareColor = {0.2f, 0.3f, 0.8f};
};

class Sandbox : public engine::Application
{
public:
	Sandbox()
		: Application()
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