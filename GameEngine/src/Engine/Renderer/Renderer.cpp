#include "ngpch.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace engine
{
	Scope<Renderer::SceneData> Renderer::s_SceneData = CreateScope<Renderer::SceneData>();
	
	void Renderer::Init()
	{
		RenderCommand::Init();
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform/* = glm::mat4(1.0f)*/)
	{
		shader->Bind();
		auto glShader = std::dynamic_pointer_cast<OpenGLShader>(shader);
		glShader->UploadUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		glShader->UploadUniformMat4("u_Transform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}
