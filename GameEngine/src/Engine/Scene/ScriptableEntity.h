#pragma once

#include "Entity.h"

namespace engine
{

	class ScriptableEntity
	{
	public:
		template<typename T>
		T& GetComponent()
		{
			return m_Entity.GetComponent<T>();
		}
		
	private:
		Entity m_Entity;
		friend class Scene;
		
	};
	
}


