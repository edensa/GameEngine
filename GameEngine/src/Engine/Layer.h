#pragma once

#include "Engine/Core.h"
#include "Engine/Events/Event.h"

namespace engine
{
	
	class ENGINE_API Layer
	{
	public:
		Layer(std::string debugName = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}

		virtual void OnUpdate() {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;

	};

}