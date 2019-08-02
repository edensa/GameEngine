#include "ngpch.h"
#include "LayerStack.h"

engine::LayerStack::LayerStack()
	: m_InsertPoint(0)
{
}

engine::LayerStack::~LayerStack()
{
	for (auto* layer : m_Layers)
		delete layer;
}

void engine::LayerStack::PushLayer(Layer* layer)
{
	m_Layers.emplace(InsertIterator(), layer);
	layer->OnAttach();
	m_InsertPoint++;
}

void engine::LayerStack::PushOverlay(Layer* overlay)
{
	m_Layers.emplace_back(overlay);
	overlay->OnAttach();
}

void engine::LayerStack::PopLayer(Layer* layer)
{
	auto it = std::find(m_Layers.begin(), InsertIterator(), layer);
	if (it != m_Layers.end())
	{
		m_Layers.erase(it);
		m_InsertPoint--;
		layer->OnDetach();
	}
}

void engine::LayerStack::PopOverlay(Layer* overlay)
{
	auto it = std::find(InsertIterator(), m_Layers.end(), overlay);
	if (it != m_Layers.end()) {
		m_Layers.erase(it);
		overlay->OnDetach();
	}
}

std::vector<engine::Layer*>::iterator engine::LayerStack::InsertIterator()
{
	auto it = m_Layers.begin();
	std::advance(it, m_InsertPoint);
	return it;
}
