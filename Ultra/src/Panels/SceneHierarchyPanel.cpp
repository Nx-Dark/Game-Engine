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

				auto& translation{ tc.Translation };
				ImGui::DragFloat3("Translate", glm::value_ptr(translation), 0.05f);

				glm::vec3 rotation{ glm::degrees(tc.Rotation) };
				if (ImGui::DragFloat3("Rotation", glm::value_ptr(rotation), 0.5f))
					tc.Rotation = glm::radians(rotation);

				auto& scale{ tc.Scale };
				ImGui::DragFloat3("Scale", glm::value_ptr(scale), 0.05f);

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