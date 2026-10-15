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

	}

	//helper static function for this translation unit to draw vec3 components cleanly
	static bool DrawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f)
	{

		bool state{};

		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0, 0 });

		float lineHeight{ GImGui->FontSize + GImGui->Style.FramePadding.y * 2.0f };
		ImVec2 buttonSize{ lineHeight + 3.0f, lineHeight };

		//X component
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		if (ImGui::Button("X", buttonSize))
			{ values.x = resetValue; state = true; }
		ImGui::PopStyleColor(3);
		ImGui::SameLine();
		if (ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f")) state = true;
		ImGui::PopItemWidth();

		ImGui::SameLine();

		//y component
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.8f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.9f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.8f, 0.15f, 1.0f });
		if (ImGui::Button("Y", buttonSize))
			{ values.y = resetValue; state = true; }
		ImGui::PopStyleColor(3);
		ImGui::SameLine();
		if(ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f")) state = true;
		ImGui::PopItemWidth();

		ImGui::SameLine();

		//z component
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.15f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.2f, 0.9f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.15f, 0.8f, 1.0f });
		if (ImGui::Button("Z", buttonSize))
			{ values.z = resetValue; state = true; }
		ImGui::PopStyleColor(3);
		ImGui::SameLine();
		if (ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f")) state = true;;
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();

		//reset the columns per row since imgui is heavuily state based
		ImGui::Columns(1); 

		ImGui::PopID();

		return state;
	}

	//helper function to draw the components of currently selected entity in the properties panel
	void SceneHierarchyPanel::DrawEntityComponents(Entity entity)
	{
		//tag component
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

		//transform component(TODO: Add rotation, Scaling and stuff);
		if (entity.HasAnyofComponent<TransformComponent>())
		{

			if (ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform")) 
			{
				auto& tc{ entity.GetComponents<TransformComponent>() };

				DrawVec3Control("Translate", tc.Translation);

				glm::vec3 rotation{ glm::degrees(tc.Rotation) };
				if (DrawVec3Control("Rotate", rotation))
					tc.Rotation = glm::radians(rotation);

				DrawVec3Control("Scale", tc.Scale, 1.0f);

				//pop
				ImGui::TreePop();

			}

			ImGui::Separator();
			ImGui::Spacing();
		}

		//camera component
		if (entity.HasAnyofComponent<CameraComponent>())
		{

			if (ImGui::TreeNodeEx((void*)typeid(CameraComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Camera"))
			{

				auto& cameraComponent{ entity.GetComponents<CameraComponent>() };
				auto& camera{ cameraComponent.Camera };

				static const char* ProjectionTypeStrings[]{ "Orthographic", "Perspective" };
				const char* currentProjectionTypeString{ ProjectionTypeStrings[(int)camera.GetProjectionType()] };

				//primary camera toggle
				ImGui::Checkbox("Primary", &cameraComponent.Primary);
				//fixed aspect ratio
				ImGui::Checkbox("FixedAspectRatio", &cameraComponent.FixedAspectRatio);

				if (ImGui::BeginCombo("Projection", currentProjectionTypeString)) {

					for (int i{}; i < 2; i++)
					{
						bool isSelected{ currentProjectionTypeString == ProjectionTypeStrings[i] };

						if (ImGui::Selectable(ProjectionTypeStrings[i], isSelected))
						{
							currentProjectionTypeString == ProjectionTypeStrings[i];
							camera.SetProjectionType((SceneCamera::ProjectionType)i);
						}

						if (isSelected)
							ImGui::SetItemDefaultFocus();
					}


					ImGui::EndCombo();
				}

				//orthographics or perspective camera components(means the projection parameters)
				switch (camera.GetProjectionType())
				{
					case SceneCamera::ProjectionType::Orthographic: 
					{

						float size{ camera.GetOrthographicSize() };
						float speed{ cameraComponent.Speed };
						float nearClip{ camera.GetOrthographicNearClip() };
						float farClip{ camera.GetOrthographicFarClip() };

						if (ImGui::DragFloat("Size", &size, 0.1f))
							camera.SetOrthographicSize(size);

						if (ImGui::DragFloat("Speed", &speed, 0.1f, 0.0f))
							cameraComponent.Speed = speed;

						if (ImGui::DragFloat("NearClip", &nearClip, 0.05f))
							camera.SetOrthographicNearClip(nearClip);

						if (ImGui::DragFloat("FarClip", &farClip, 0.05f))
							camera.SetOrthographicFarClip(farClip);

						break;
					};

					case SceneCamera::ProjectionType::Perspective: 
					{
						float fovy{ glm::degrees(camera.GetPerspectiveVerticalFov()) };
						float speed{ cameraComponent.Speed };
						float nearClip{ camera.GetPerspectiveNearClip() };
						float farClip{ camera.GetPerspectiveFarClip() };

						if(ImGui::DragFloat("Speed", &speed, 0.1f))
							cameraComponent.Speed = speed;

						if (ImGui::DragFloat("Fov", &fovy, 1.0f, 0.0f, 180.0f))
							camera.SetPerspectiveVerticalFov(glm::radians(fovy));

						if (ImGui::DragFloat("NearClip", &nearClip, 0.1f))
							camera.SetPerspectiveNearClip(nearClip);

						if (ImGui::DragFloat("FarClip", &farClip, 0.1f))
							camera.SetPerspectiveFarClip(farClip);

						break;
					};

				}

				//pop
				ImGui::TreePop();

			}

			ImGui::Separator();
			ImGui::Spacing();
		}

		if (entity.HasAnyofComponent<SpriteRendererComponent>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(SpriteRendererComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Sprite Renderer"))
			{

				auto& spriteRenderer{ entity.GetComponents<SpriteRendererComponent>() };
				ImGui::ColorEdit4("Color", glm::value_ptr(spriteRenderer.Color));

				//pop
				ImGui::TreePop();

			}

			ImGui::Separator();
		}

	}

}