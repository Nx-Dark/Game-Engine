#pragma once

#include "Dark/Core/Core.h"

#include <Dark/Core/Layer.h>

#include <Dark/Events/ApplicationEvent.h>
#include <Dark/Events/KeyEvent.h>
#include <Dark/Events/MouseEvent.h>

namespace Dark {

	class DARK_API ImGuiLayer : public Layer {

	private:

		float m_Time{};
	
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		//begin and end ImGuiWindow rendering
		void Begin();
		void End();

	};

}