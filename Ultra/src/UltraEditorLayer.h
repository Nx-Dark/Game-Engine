#pragma once

#include <Dark.h>

namespace Dark {

	class UltraEditorLayer : public Layer
	{

	private:

		Ref<Texture2D> m_SpriteSheet;
		Ref<Framebuffer> m_Framebuffer;

		OrthoGraphicCameraController m_Camera;

		std::unordered_map<char, Ref<SubTexture2D>> m_TileHashMap;

		Ref<AudioData> m_Music{};

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