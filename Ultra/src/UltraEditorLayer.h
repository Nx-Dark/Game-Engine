#pragma once

#include <Dark.h>

namespace Dark {

	class UltraEditorLayer : public Layer
	{

	private:

		Ref<Texture2D> m_SpriteSheet;
		Ref<Framebuffer> m_Framebuffer;

		OrthoGraphicCameraController m_CameraController;

		std::unordered_map<char, Ref<SubTexture2D>> m_TileHashMap;

		Ref<AudioData> m_Music{};

		Entity m_SquareEntity{};
		Entity m_CameraEntity{};
		Entity m_SecondCamera{};
		bool m_PrimaryCamera{true};
		
		Ref<Scene> m_ActiveScene{};

		bool m_ViewportFocused{};
		bool m_ViewportHovered{};
		glm::vec2 m_ViewportPanelSize{ 1.0f, 1.0f };

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