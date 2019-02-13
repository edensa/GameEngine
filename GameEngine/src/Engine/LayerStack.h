#pragma once

#include "Engine/Core.h"
#include "Layer.h"

namespace engine
{
	
	class ENGINE_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
	private:
		std::vector<Layer*>::iterator InsertIterator();

		std::vector<Layer*> m_Layers;
		size_t m_InsertPoint;
	};

}