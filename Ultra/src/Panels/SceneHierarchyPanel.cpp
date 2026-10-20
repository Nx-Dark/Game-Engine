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
			
		//creating entities live(right click on a blank space in scene hierarchy panel)
		if (ImGui::BeginPopupContextWindow(0, (ImGuiPopupFlags_MouseButtonRight | ImGuiPopupFlags_NoOpenOverItems | ImGuiPopupFlags_NoOpenOverExistingPopup)))
		{
			//creating the entity
			if(ImGui::MenuItem("Create Empty Entity"))
				m_Context->CreateEntity("Empty Entity");

			ImGui::EndPopup();
		}

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

		flags |= ImGuiTreeNodeFlags_SpanAvailWidth;

		bool treeNodeExpanded{ ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, "%s", tag.c_str()) };

		//it checks if the last item is clicked or selected
		if (ImGui::IsItemClicked())
		{
			m_EntitySelection = entity;
		}


		bool isEntityTobeDestroyed{};
		if (ImGui::BeginPopupContextItem(0, (ImGuiPopupFlags_MouseButtonRight))) 
		{

			if (ImGui::MenuItem("Destroy Entity"))
				isEntityTobeDestroyed = true;

			ImGui::EndPopup();
		}


		if (treeNodeExpanded) 
		{
			ImGuiTreeNodeFlags flags{ ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth };

			bool treeNodeExpanded{ ImGui::TreeNodeEx((void*)23028742, flags, "%s", tag.c_str()) };

			if (treeNodeExpanded)
				ImGui::TreePop();

			ImGui::TreePop();
		}

		if (isEntityTobeDestroyed) {
			if (m_EntitySelection == entity)
				m_EntitySelection = {};

			m_Context->DestroyEntity(entity);
		}
	}

	//helper static function for this translation unit to draw vec3 components cleanly
	static bool DrawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f)
	{

		ImGuiIO& io{ ImGui::GetIO() };
		auto opensansBoldFont{ io.Fonts->Fonts[std::to_underlying(ImGuiLayer::FontType::OpenSansBold)]};

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
		ImGui::PushFont(opensansBoldFont);
		if (ImGui::Button("X", buttonSize))
			{ values.x = resetValue; state = true; }
		ImGui::PopFont();
		ImGui::PopStyleColor(3);
		ImGui::SameLine();
		if (ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f")) state = true;
		ImGui::PopItemWidth();

		ImGui::SameLine();

		//y component
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.8f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.9f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.8f, 0.15f, 1.0f });
		ImGui::PushFont(opensansBoldFont);
		if (ImGui::Button("Y", buttonSize))
			{ values.y = resetValue; state = true; }
		ImGui::PopFont();
		ImGui::PopStyleColor(3);
		ImGui::SameLine();
		if(ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f")) state = true;
		ImGui::PopItemWidth();

		ImGui::SameLine();

		//z component
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.15f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.2f, 0.9f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.15f, 0.8f, 1.0f });
		ImGui::PushFont(opensansBoldFont);
		if (ImGui::Button("Z", buttonSize))
			{ values.z = resetValue; state = true; }
		ImGui::PopFont();
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


	//templated drawentitycomponente
	//UI func takes in a function pointer/lambda which has the UI specific code and this templated function contains the general boiler plate codes
	template<typename _Type, typename UIFunc>
	static void DrawEntityComponent(const std::string& label, Entity entity, bool canBeDeleted, UIFunc uiFunc)
	{
		if (entity.HasAnyofComponent<_Type>()) {

			const ImGuiTreeNodeFlags treeNodeFlags{ ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth |
				ImGuiTreeNodeFlags_AllowOverlap | ImGuiTreeNodeFlags_FramePadding };

			ImVec2 contentRegionAvail{ ImGui::GetContentRegionAvail() };

			auto& component{ entity.GetComponents<_Type>() };

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
			float lineHeight{ GImGui->FontSize + GImGui->Style.FramePadding.y * 2.0f };
			ImGui::Separator();
			bool open{ ImGui::TreeNodeEx((void*)typeid(_Type).hash_code(), treeNodeFlags, label.c_str()) };
			ImGui::PopStyleVar();
			ImGui::SameLine(contentRegionAvail.x - lineHeight * 0.5f);
			if (ImGui::Button("+", ImVec2{ lineHeight, lineHeight }))
				ImGui::OpenPopup("ComponentSettings");

			bool deleteComponent{};
			if (ImGui::BeginPopup("ComponentSettings"))
			{

				if (canBeDeleted && ImGui::MenuItem("Remove Component"))
					deleteComponent = true;

				ImGui::EndPopup();
			}

			if (open)
			{
				uiFunc(component);
				//pop
				ImGui::TreePop();

			}

			//deferred component removal
			if (deleteComponent)
				entity.RemoveComponent<_Type>();

			ImGui::Separator();
			ImGui::Spacing();

		}
	}

	//helper function to draw the components of currently selected entity in the properties panel
	void SceneHierarchyPanel::DrawEntityComponents(Entity entity)
	{
		//tag component(special case);
		if (entity.HasAnyofComponent<TagComponent>())
		{
			auto& tag{ entity.GetComponents<TagComponent>().Tag };

			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			strcpy_s(buffer, sizeof(buffer), tag.c_str());
			if (ImGui::InputText("##Tag", buffer, sizeof(buffer)))
			{
				tag = std::string(buffer);
			}
		}

		ImGui::SameLine();
		ImGui::PushItemWidth(-1);

		//creating components for the currently selected entity
		if (ImGui::Button("Add Component"))
			ImGui::OpenPopup("AddComponent");

		if (ImGui::BeginPopup("AddComponent"))
		{
			if (ImGui::MenuItem("Camera"))
			{
				m_EntitySelection.AddComponent<CameraComponent>();
				ImGui::CloseCurrentPopup();
			}

			if (ImGui::MenuItem("Sprite Renderer"))
			{
				m_EntitySelection.AddComponent<SpriteRendererComponent>();
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}
		ImGui::PopItemWidth();

		ImGui::Separator();
		ImGui::Spacing();

		DrawEntityComponent<TransformComponent>("Transform", entity, false, [](TransformComponent& tc) -> void
		{
			DrawVec3Control("Translate", tc.Translation);

			glm::vec3 rotation{ glm::degrees(tc.Rotation) };
			if (DrawVec3Control("Rotate", rotation))
				tc.Rotation = glm::radians(rotation);

			DrawVec3Control("Scale", tc.Scale, 1.0f);
		});

		//camera component
		DrawEntityComponent<CameraComponent>("Camera", entity, true, [](CameraComponent& cameraComponent) -> void
		{
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

					if (ImGui::DragFloat("Speed", &speed, 0.1f))
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
		});


		//sprite renderer component
		DrawEntityComponent<SpriteRendererComponent>("Sprite Renderer", entity, true, [](auto& src) -> void 
		{
			ImGui::ColorEdit4("Color", glm::value_ptr(src.Color));
		});

	}

}