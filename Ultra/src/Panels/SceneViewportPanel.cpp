#include "dpch.h"

#include "SceneViewportPanel.h"

#include <ImGuizmo/ImGuizmo.h>

namespace Dark
{

	SceneViewportPanel::SceneViewportPanel(const Ref<Scene>& scene)
	{
		SetContext(scene);
	}
	
	void SceneViewportPanel::OnEvent(Event& e)
	{
		EventDispatcher dispatcher{ e };

		dispatcher.Dispatch<KeyPressedEvent>(DARK_BIND_EVENT_FN(SceneViewportPanel::OnKeyPressed));
	}

	bool SceneViewportPanel::OnKeyPressed(KeyPressedEvent& e)
	{
		switch (e.GetKeyCode())
		{
			//shortcut keys for gizmos
			case KeyCode::KEY_E:
				m_GizmoType = -1;
				break;
			case KeyCode::KEY_R:
				m_GizmoType = ImGuizmo::OPERATION::TRANSLATE;
				break;
			case KeyCode::KEY_T:
				m_GizmoType = ImGuizmo::OPERATION::ROTATE;
				break;
			case KeyCode::KEY_Y:
				m_GizmoType = ImGuizmo::OPERATION::SCALE;
				break;
		}

		return false;
	}
	
	void SceneViewportPanel::OnImGuiRender(const EditorCamera& editorCamera, const Ref<Framebuffer>& frameBuffer, Entity selectedEntity)
	{
		//viewport
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.0f, 0.0f });
		if (ImGui::Begin("Viewport")) //viewport
		{
			//if the viewport is focused or hovered
			m_ViewportFocused = ImGui::IsWindowFocused();
			m_ViewportHovered = ImGui::IsWindowHovered();
			Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused && !m_ViewportHovered);

			m_ViewportPanelSize = { ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y };

			//rendering the framebuffer to the viewport panel
			ImGui::Image((void*)frameBuffer->GetColorAttachmentRendererID(1), { m_ViewportPanelSize.x, m_ViewportPanelSize.y }, { 0.0f, 1.0f }, { 1.0f, 0.0f });

			//Gizmos
			m_EntitySelection = { selectedEntity };
			if (m_EntitySelection && (m_GizmoType != -1))
			{
				ImGuizmo::SetOrthographic(false);
				ImGuizmo::SetDrawlist();

				float windowW{ static_cast<float>(ImGui::GetWindowWidth()) };
				float windowH{ static_cast<float>(ImGui::GetWindowHeight()) };
				ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowW, windowH);

				//runtime camera/scene camera from the ECS
				//auto cameraEntity{ m_ActiveScene->GetPrimaryCameraEntity() };
				//const auto& camera{ cameraEntity.GetComponents<CameraComponent>().Camera };
				//const auto& cameraProjection{ camera.GetProjection() };
				//glm::mat4 cameraView{ glm::inverse(cameraEntity.GetComponents<TransformComponent>().GetTransform()) };

				//editor camera 
				const glm::mat4& cameraProjection{ editorCamera.GetProjection() };
				const glm::mat4& cameraView{ editorCamera.GetViewMatrix() };

				//Currently Selected Entity transform
				auto& entityTc{ m_EntitySelection.GetComponents<TransformComponent>() };
				glm::mat4 entityTransform{ entityTc.GetTransform() };

				//snapping
				bool snap{ Input::IsKeyPressed(KeyCode::KEY_LEFT_CONTROL) };
				float snapVal{ (m_GizmoType == ImGuizmo::OPERATION::ROTATE) ? 45.0f : 0.5f }; //0.5m for translation/scale and 45.0f degree for rotation;

				const float snapValues[3]{ snapVal, snapVal, snapVal };

				ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection), (ImGuizmo::OPERATION)m_GizmoType,
					ImGuizmo::MODE::LOCAL, glm::value_ptr(entityTransform), nullptr, (snap ? snapValues : nullptr));

				if (ImGuizmo::IsUsing())
				{
					Math::DecomposeTransfrom(entityTransform, entityTc.Translation, entityTc.Rotation, entityTc.Scale);
				}
			}
		}
		ImGui::End(); //viewport
		ImGui::PopStyleVar();
	}

}