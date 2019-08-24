#include <Engine.h>

#include <imgui.h>

class ExampleLayer : public engine::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
		, m_Camera(-1.6, 1.6f, -0.9f, 0.9f)
		, m_CameraPosition(0.f)
	{
		m_VertexArray.reset(engine::VertexArray::Create());

		float verticies[7 * 3] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f,
		};

		std::shared_ptr<engine::VertexBuffer> vertexBuffer;
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

		std::shared_ptr<engine::IndexBuffer> indexBuffer;
		indexBuffer.reset(engine::IndexBuffer::Create(indicies, sizeof(indicies) / sizeof(uint32_t)));

		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(engine::VertexArray::Create());

		float squareVerticies[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f,
		};

		std::shared_ptr<engine::VertexBuffer> squareVB;
		squareVB.reset(engine::VertexBuffer::Create(squareVerticies, sizeof(squareVerticies)));

		squareVB->SetLayout({
			{ engine::ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		unsigned squareIndicies[6] = {
			0, 1, 2, 2, 3, 0
		};

		std::shared_ptr<engine::IndexBuffer> squareIB;
		squareIB.reset(engine::IndexBuffer::Create(squareIndicies, sizeof(squareIndicies) / sizeof(uint32_t)));

		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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

		m_Shader.reset(engine::Shader::Create(vertexSrc, fragmentSrc));

		std::string blueVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";
		std::string blueFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_BlueShader.reset(engine::Shader::Create(blueVertexSrc, blueFragmentSrc));
	}

	void OnUpdate(engine::Timestep ts) override
	{
		ENGINE_TRACE("Delta time {0}", ts.GetSeconds());
		
		if (engine::Input::IsKeyPressed(ENGINE_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;

		else if (engine::Input::IsKeyPressed(ENGINE_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (engine::Input::IsKeyPressed(ENGINE_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;

		else if (engine::Input::IsKeyPressed(ENGINE_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		else if (engine::Input::IsKeyPressed(ENGINE_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;

		else if (engine::Input::IsKeyPressed(ENGINE_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		engine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		engine::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		engine::Renderer::BeginScene(m_Camera);

		engine::Renderer::Submit(m_BlueShader, m_SquareVA);
		engine::Renderer::Submit(m_Shader, m_VertexArray);

		engine::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnEvent(engine::Event& event) override
	{
		engine::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<engine::KeyPressedEvent>(BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
		//ENGINE_TRACE("{0}", event);
	}

	bool OnKeyPressedEvent(engine::KeyPressedEvent& event)
	{
		return false;
	}

private:
	std::shared_ptr<engine::Shader> m_Shader;
	std::shared_ptr<engine::Shader> m_BlueShader;
	std::shared_ptr<engine::VertexArray> m_VertexArray;
	std::shared_ptr<engine::VertexArray> m_SquareVA;

	engine::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;
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