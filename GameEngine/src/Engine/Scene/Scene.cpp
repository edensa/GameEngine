#include "ngpch.h"
#include "Scene.h"

#include "Engine/Renderer/Renderer2D.h"
#include "Engine/Scene/Component.h"
#include "Engine/Scene/Entity.h"

#include "glm/glm.hpp"

namespace engine
{
	Scene::Scene()
	{
#if ENTT_EXAMPLE_CODE
		struct MeshComponent
		{
			
		};
		
		struct TransformComponent
		{
			glm::mat4 Transform;

			TransformComponent() = default;
			TransformComponent(const TransformComponent&) = default;
			TransformComponent(const glm::mat4& transform)
				: Transform(transform) {}
			operator glm::mat4&() { return Transform; }
			operator const glm::mat4&() const { return Transform; }
		};

		entt::entity entity = m_Registry.create();
		m_Registry.emplace<TransformComponent>(entity, glm::mat4(1.0f));

		if (m_Registry.has<TransformComponent>(entity))
			TransformComponent& transform = m_Registry.get<TransformComponent>(entity);

		auto view = m_Registry.view<TransformComponent>();
		for (auto entity : view)
		{
			TransformComponent& transform = m_Registry.get<TransformComponent>(entity);
		}

		auto group = m_Registry.group<TransformComponent>(entt::get<MeshComponent>);
		for (auto entity : group)
		{
			auto&[transform, mesh] = m_Registry.get<TransformComponent, MeshComponent>(entity);

		}
#endif
	}

	Entity Scene::CreateEntity(const std::string& name/* = std::string()*/)
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Entity" : name;
		return entity;
	}

	void Scene::OnUpdate(Timestep ts)
	{

		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for (auto entity : group)
		{
			auto& [transform, sprite] = m_Registry.get<TransformComponent, SpriteRendererComponent>(entity);

			Renderer2D::DrawQuad(transform, sprite.Color);
		}
		
	}
}
