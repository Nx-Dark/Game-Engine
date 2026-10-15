#pragma once

#include "Dark.h"
#include "Panels/SceneHierarchyPanel.h"

namespace Dark {

	class UltraEditorLayer : public Layer
	{

	private:

		Ref<Texture2D> m_SpriteSheet;
		Ref<Framebuffer> m_Framebuffer;

		std::unordered_map<char, Ref<SubTexture2D>> m_TileHashMap;

		Ref<AudioData> m_Music{};
		
		Ref<Scene> m_ActiveScene{};

		bool m_ViewportFocused{};
		bool m_ViewportHovered{};
		glm::vec2 m_ViewportPanelSize{ 1.0f, 1.0f };

		//panels
		SceneHierarchyPanel m_SceneHierarchyPanel{};

	public:
		UltraEditorLayer();
		virtual ~UltraEditorLayer();

		void OnAttach() override;
		void OnDetach() override;

		void OnUpdate(DeltaTime dt) override;
		void OnEvent(Event& e) override;

		void OnImGuiRender() override;

	};

}