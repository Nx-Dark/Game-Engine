#include "SceneHierarchyPanel.h"

namespace Dark
{

	SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& context)
	{
		SetContext(context);
	}

	void SceneHierarchyPanel::SetContext(const Ref<Scene>& context)
	{
		m_Context = context;
	}

	void SceneHierarchyPanel::OnImGuiRender()
	{
		//scene hierarchy
		ImGui::Begin("Scene Hierarchy");
	
		m_Context->m_Registry.view<entt::entity>().each([&](const auto entityID) 
		{

			Entity entity{ entityID, m_Context.get() };
			DrawEntityNode(entity); //drawing the entity node in the scene hierarchy or display it(whatever);

		});


		//deseleting entities
		if (ImGui::IsMouseDown(ImGuiMouseButton_Left) && ImGui::IsWindowHovered())
			m_EntitySelection = { };
		//--------------------
			

		ImGui::End();

		//properties panel
		//TODO: Move into its own class and stuff
		ImGui::Begin("Properties");

		if (m_EntitySelection)
		{
			DrawEntityComponents(m_EntitySelection);
		}

		ImGui::End();
	}

	//helper function to draw an entity node in the scene hierarchy panel
	void SceneHierarchyPanel::DrawEntityNode(Entity entity)
	{
		auto& tag{ entity.GetComponents<TagComponent>().Tag };
		
		ImGuiTreeNodeFlags flags{
			((m_EntitySelection == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow
		};

		bool treeNodeExpanded{ ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, "%s", tag.c_str()) };

		//it checks if the last item is clicked or selected
		if (ImGui::IsItemClicked())
		{
			m_EntitySelection = entity;
		}

		if (treeNodeExpanded)
		{

			ImGuiTreeNodeFlags flags{
				ImGuiTreeNodeFlags_OpenOnArrow
			};

			bool treeNodeExpanded{ ImGui::TreeNodeEx((void*)7850987243, flags, "%s", tag.c_str()) };

			if (treeNodeExpanded)
				ImGui::TreePop();

			ImGui::TreePop();
		}

	}

	void SceneHierarchyPanel::DrawEntityComponents(Entity entity)
	{
		if (entity.HasAnyofComponent<TagComponent>())
		{
			auto& tag{ entity.GetComponents<TagComponent>().Tag };

			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			strcpy_s(buffer, sizeof(buffer), tag.c_str());
			if (ImGui::InputText("Tag", buffer, sizeof(buffer)))
			{
				tag = std::string(buffer);
			}

			ImGui::Separator();
			ImGui::Spacing();
		}

		if (entity.HasAnyofComponent<TransformComponent>())
		{

			if (ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform")) 
			{
				auto& transform{ entity.GetComponents<TransformComponent>().Transform };
				ImGui::DragFloat3("Translate", glm::value_ptr(transform[3]), 0.05f);

				//pop
				ImGui::TreePop();

			}
		}
	}

}