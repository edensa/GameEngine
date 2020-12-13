#pragma once
#include <entt.hpp>

#include "Engine/Core/Timestep.h"

namespace engine
{

	class Entity;

	class Scene
	{
	public:
		Scene();

		Entity CreateEntity(const std::string& name = std::string());
		
		void OnUpdate(Timestep ts);
		void OnViewportResize(uint32_t width, uint32_t height);

	private:
		entt::registry m_Registry;
		uint32_t m_ViewportWidth = 0;
		uint32_t m_ViewportHeight = 0;
		
		friend class Entity;
		friend class SceneHierarchyPanel;
	};
	
}
