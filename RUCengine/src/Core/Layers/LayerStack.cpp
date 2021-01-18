#include "LayerStack.h"

namespace RUC
{
	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
		{
			layer->OnDetach();
			delete layer;
		}
	}

	void LayerStack::Push(Layer* layer)
	{
		m_Layers.push_back(layer);
		layer->OnAttach();
	}

	void LayerStack::PushOnTop(Layer* layer) 
	{
		m_Layers.emplace(m_Layers.begin(), layer);
		layer->OnAttach();
	}
}