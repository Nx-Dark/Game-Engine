#pragma once

#include "Dark/Core/Core.h"

#include <Dark/Core/Layer.h>

#include <Dark/Events/ApplicationEvent.h>
#include <Dark/Events/KeyEvent.h>
#include <Dark/Events/MouseEvent.h>

namespace Dark {

	class DARK_API ImGuiLayer : public Layer {

	public:
		enum class FontType : uint32_t {
			OpenSansRegular = 0, OpenSansBold = 1
		};

	private:

		bool m_BlockEvents{false};
		float m_Time{};
	
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;

		//begin and end ImGuiWindow rendering
		void Begin();
		void End();

		inline void BlockEvents(bool _block) { m_BlockEvents = _block; }

		//theme and shit
		void SetDarkThemeColors();
	};

}