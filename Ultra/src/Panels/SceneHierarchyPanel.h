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
		void SetContext(const Ref<Scene>& context);

		//rendering the imgui panel cause obviously
		void OnImGuiRender();

	private:
		void DrawEntityNode(Entity entity);
		void DrawEntityComponents(Entity entity);
	};


}