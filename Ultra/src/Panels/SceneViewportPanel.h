#pragma once

#include "Dark.h"

#include "SceneHierarchyPanel.h"

namespace Dark
{

	class SceneViewportPanel
	{
	private:

		Ref<Scene> m_Context{};

		Entity m_EntitySelection{};

		bool m_ViewportHovered{};
		bool m_ViewportFocused{};
		glm::vec2 m_ViewportPanelSize{ 1.0f };
		glm::vec2 m_ViewportBounds[2]{};

		//imguizo shit
		int m_GizmoType{ -1 };

	public:
		SceneViewportPanel() = default;
		SceneViewportPanel(const Ref<Scene>& context);
		~SceneViewportPanel() = default;

		inline void SetContext(const Ref<Scene>& context) { m_Context = context; m_EntitySelection = {}; }

		void OnEvent(Event& e);
		void OnImGuiRender(const EditorCamera& editorCamera, const Ref<Framebuffer>& frameBuffer, Entity selectedEntity);

		//getters and settets
		inline Entity GetSelectedEntity() const { return m_EntitySelection; }
		inline void SetSelectedEntity(Entity entity) { m_EntitySelection = entity; }

		inline const glm::vec2& GetViewportPanelSize() const { return m_ViewportPanelSize; }
		inline void SetViewportPanelSize(const glm::vec2& _size) { m_ViewportPanelSize = _size; }

		inline const glm::vec2* GetViewportPanelBounds() const { return m_ViewportBounds; }
		inline void SetViewportPanelBounds(const glm::vec2& _minBounds, const glm::vec2& _maxBounds) { m_ViewportBounds[0] = _minBounds; m_ViewportBounds[1] = _maxBounds; }

		inline bool GetViewportHovered() const { return m_ViewportHovered; }
		inline bool GetViewportFocused() const { return m_ViewportFocused; }
		inline void SetViewportHovered(bool val) { m_ViewportHovered = val; }
		inline void SetViewportFocused(bool val) { m_ViewportFocused = val; }

		inline int GetGizmoType() const { return m_GizmoType; }
		inline void SetGizmoType(int _type) { m_GizmoType = _type; }

	private:
		bool OnKeyPressed(KeyPressedEvent& e);
	}; 

}