#include "ngpch.h"
#include "Entity.h"

namespace engine
{
	Entity::Entity()
		: m_EntityHandle(entt::null)
		, m_Scene(nullptr)
	{ }

	Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityHandle(handle)
		, m_Scene(scene)
	{ }

}
