#pragma once

#include "Dark.h"

namespace Dark
{

	class SceneHierarchyPanel
	{
	private:

		Ref<Scene> m_Context{};

		//currently selected entity in the panel;
		Entity m_EntitySelection{};

	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& scene);
		
		//context is the scene which we are selecting for the scene hierarchy panel
		inline void SetContext(const Ref<Scene>& context) { m_Context = context; m_EntitySelection = {}; }

		//rendering the imgui panel cause obviously
		void OnImGuiRender();

		//getter for the selected entity;
		inline Entity GetSelectedEntity() const { return m_EntitySelection; }

	private:
		void DrawEntityNode(Entity entity);
		void DrawEntityComponents(Entity entity);
	};


}