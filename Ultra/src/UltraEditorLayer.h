#pragma once

#include "Dark.h"
#include "Panels/SceneHierarchyPanel.h"
#include "Panels/SceneViewportPanel.h"
#include "Dark/Renderer/EditorCamera.h"

namespace Dark {

	class UltraEditorLayer : public Layer
	{

	private:
		
		Ref<Framebuffer> m_Framebuffer{};

		Ref<Scene> m_ActiveScene{};

		//panels
		SceneViewportPanel m_SceneViewportPanel{};
		SceneHierarchyPanel m_SceneHierarchyPanel{};

		//editor settings stuff
		bool m_ShowEditorSettings{};

		//editor camera
		EditorCamera m_EditorCamera;

	public:
		UltraEditorLayer();
		virtual ~UltraEditorLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate(DeltaTime dt) override;
		virtual void OnEvent(Event& e) override;

		virtual void OnImGuiRender() override;

	private:
		bool OnKeyPressed(KeyPressedEvent& e);

		void NewSceneFile();
		void OpenSceneFile();
		void SaveSceneFileAs();

		//menu stuff
		void EditorSettingsMenu();
	};

}