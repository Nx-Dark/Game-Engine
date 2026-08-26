#pragma once

#include "Dark/Core/Core.h"
#include "Dark/Events/Event.h"

#include "Dark/Core/DeltaTime.h"

namespace Dark {
	class DARK_API Layer
	{
	protected:

		std::string m_Name{};

	public:
		Layer(const std::string& u_LayerName = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnImGuiRender() {}
		virtual void OnUpdate(DeltaTime dt) {}
		virtual void OnEvent(Event& e) {}

		inline const std::string& GetLayerName() { return m_Name; }
	};

}