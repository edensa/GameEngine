#include "ngpch.h"
#include "Renderer2D.h"

#include "Platform/OpenGL/OpenGLShader.h"
#include "RenderCommand.h"
#include "Shader.h"
#include "VertexArray.h"

namespace engine
{

	struct Renderer2DStorage
	{
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> FlatColorShader;
	};

	static Scope<Renderer2DStorage> s_Data;
	
	void Renderer2D::Init()
	{
		s_Data = CreateScope<Renderer2DStorage>();
		
		s_Data->QuadVertexArray = engine::VertexArray::Create();

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
		s_Data->QuadVertexArray->AddVertexBuffer(squareVB);

		unsigned squareIndicies[6] = { 0, 1, 2, 2, 3, 0 };
		engine::Ref<engine::IndexBuffer> squareIB;
		squareIB.reset(engine::IndexBuffer::Create(squareIndicies, sizeof(squareIndicies) / sizeof(uint32_t)));
		s_Data->QuadVertexArray->SetIndexBuffer(squareIB);

		s_Data->FlatColorShader = Shader::Create("assets/shaders/FlatColorShader.glsl");
	}

	void Renderer2D::Shutdown()
	{
		s_Data.reset(nullptr);
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		auto glShader = std::dynamic_pointer_cast<engine::OpenGLShader>(s_Data->FlatColorShader);
		glShader->Bind();
		glShader->UploadUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		glShader->UploadUniformMat4("u_Transform", glm::mat4(1.0f));
	}

	void Renderer2D::EndScene()
	{
	}
	
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0 }, size, color);
	}
	
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		auto glShader = std::dynamic_pointer_cast<engine::OpenGLShader>(s_Data->FlatColorShader);
		glShader->Bind();
		glShader->UploadUniformFloat4("u_Color", color);

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}
}
