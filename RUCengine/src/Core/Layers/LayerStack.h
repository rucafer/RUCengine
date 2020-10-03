#pragma once

#include "Layer.h"

#include <vector>

namespace RUC
{

	class LayerStack
	{
	public:
		LayerStack() = default;
		~LayerStack();

		void PushOnTop(Layer* layer);
		void Push(Layer* layer);

		void Remove(Layer* layer);

		//Iterators
		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
		std::vector<Layer*>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
		std::vector<Layer*>::reverse_iterator rend() { return m_Layers.rend(); }

		std::vector<Layer*>::const_iterator begin() const{ return m_Layers.begin(); }
		std::vector<Layer*>::const_iterator end() const { return m_Layers.end(); }
		std::vector<Layer*>::const_reverse_iterator rbegin() const { return m_Layers.rbegin(); }
		std::vector<Layer*>::const_reverse_iterator rend() const { return m_Layers.rend(); }

	private:

	private:
		std::vector<Layer*> m_Layers;
	};

}