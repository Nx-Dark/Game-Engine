#pragma once

#include "Dark/Core/Core.h"

#include "Dark/Events/Event.h"

namespace Dark {

	//a forward decl for Layer object/class
	class Layer;

	class DARK_API LayerStack
	{

		std::vector<Layer*> m_Layers{};
		
		int m_LayerInsertIndex{0};

	public:

		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		void PopOverlay(Layer* layer);

		inline auto begin() { return m_Layers.begin(); }
		inline auto end() { return m_Layers.end(); }
		inline auto rbegin() { return m_Layers.rbegin(); }
		inline auto rend() { return m_Layers.rend(); }

		inline const std::vector<Layer*>& GetLayers() { return m_Layers; }
	};

}