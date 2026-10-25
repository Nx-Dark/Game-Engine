#include "UltraEditorLayer.h"

#include "Dark/Scene/SceneSerializer.h"

#include "ImGuizmo/ImGuizmo.h"

namespace Dark {

	UltraEditorLayer::UltraEditorLayer()
		: Layer("UltraEditorLayer")
	{
	}

	UltraEditorLayer::~UltraEditorLayer()
	{

	}

	void UltraEditorLayer::OnAttach()
	{

		//framebuffer
		Dark::FramebufferSpecifications fbSpec;
		fbSpec.Width = Dark::Application::Get().GetWindow().GetWidth();
		fbSpec.Height = Dark::Application::Get().GetWindow().GetHeight();
		m_Framebuffer = Dark::Framebuffer::Create(fbSpec);

		//active scene
		m_ActiveScene = CreateRef<Scene>();

#if 0
		auto squareEntity = m_ActiveScene->CreateEntity("Orange Square");
		squareEntity.AddComponent<SpriteRendererComponent>(glm::vec4{ 1.0f, 0.5f, 0.0f, 1.0f });

		auto greenSquare{ m_ActiveScene->CreateEntity("Green Square") };
		greenSquare.AddComponent<SpriteRendererComponent>(glm::vec4{ 0.05f, 1.0f, 0.05f, 1.0f });

		//camera entity and camera component
		auto cameraA{ m_ActiveScene->CreateEntity("Camera A") };
		cameraA.AddComponent<CameraComponent>().Primary = true;
		
		auto cameraB = m_ActiveScene->CreateEntity("Camera B");
		cameraB.AddComponent<CameraComponent>();

		//camera controller script
		class CameraController : public ScriptableEntity
		{

		public:
			virtual void OnCreate() override
			{
				DARK_CORE_WARN("CameraController Script Instantiated!");
			}

			virtual void OnDestroy() override
			{
			}

			virtual void OnUpdate(DeltaTime dt) override
			{

				if (HasAnyofComponent<CameraComponent>())
				{
					auto& camComp{ GetComponents<CameraComponent>() };

					if (camComp.Primary) {

						auto& camera{ camComp.Camera };
						auto& translation{ GetComponents<TransformComponent>().Translation };
						float speed{ camComp.Speed };

						if (Input::IsKeyPressed(KeyCode::KEY_A))
							translation.x -= speed * dt;

						if (Input::IsKeyPressed(KeyCode::KEY_D))
							translation.x += speed * dt;

						if (camera.GetProjectionType() == SceneCamera::ProjectionType::Perspective ? Input::IsKeyPressed(KeyCode::KEY_SPACE) :
							Input::IsKeyPressed(KeyCode::KEY_W))
							translation.y += speed * dt;

						if (camera.GetProjectionType() == SceneCamera::ProjectionType::Perspective ? Input::IsKeyPressed(KeyCode::KEY_LEFT_SHIFT) :
							Input::IsKeyPressed(KeyCode::KEY_S))
							translation.y -= speed * dt;

						if (camera.GetProjectionType() == SceneCamera::ProjectionType::Perspective)
						{
							if (Input::IsKeyPressed(KeyCode::KEY_W))
								translation.z -= speed * dt;

							if (Input::IsKeyPressed(KeyCode::KEY_S))
								translation.z += speed * dt;
						}

					}

				}

			}
		};

		class SquareScript : public ScriptableEntity
		{
		private:

		public:

			virtual void OnCreate() override
			{

			}

			virtual void OnDestroy() override
			{

			}

			virtual void OnUpdate(DeltaTime dt) override
			{
				auto& rotation{ GetComponents<TransformComponent>().Rotation };

				rotation.y += dt;
			}
		};

		cameraA.AddComponent<NativeScriptComponent>().Bind<CameraController>();
		cameraB.AddComponent<NativeScriptComponent>().Bind<CameraController>();

		squareEntity.AddComponent<NativeScriptComponent>().Bind<SquareScript>();
#endif

		//panels
		m_SceneViewportPanel.SetContext(m_ActiveScene);
		m_SceneHierarchyPanel.SetContext(m_ActiveScene);

		//editor camera
		m_EditorCamera = EditorCamera{ { 0.0f, 0.0f, 10.0f }, (uint32_t)m_SceneViewportPanel.GetViewportPanelSize().x, 
			(uint32_t)m_SceneViewportPanel.GetViewportPanelSize().y, glm::radians(60.0f), 0.01f, 10000.0f};

	}

	void UltraEditorLayer::OnDetach()
	{

	}

	void UltraEditorLayer::OnUpdate(DeltaTime dt)
	{

		//resizing the framebuffer and the viewport panel
		const glm::vec2& sceneViewportPanelSize{ m_SceneViewportPanel.GetViewportPanelSize() };
		if (const auto& frameBufferSpec{ m_Framebuffer->GetSpecifications() };
			sceneViewportPanelSize.x != 0.0f && sceneViewportPanelSize.y != 0.0f
			&& (frameBufferSpec.Width != sceneViewportPanelSize.x || frameBufferSpec.Height != sceneViewportPanelSize.y))
		{
			m_Framebuffer->ReSize((uint32_t)sceneViewportPanelSize.x, (uint32_t)sceneViewportPanelSize.y);

			//resizing the viewport of the current active scene and editor camera;
			m_ActiveScene->OnViewportResize((uint32_t)sceneViewportPanelSize.x, (uint32_t)sceneViewportPanelSize.y);
			m_EditorCamera.SetViewportSize((uint32_t)sceneViewportPanelSize.x, (uint32_t)sceneViewportPanelSize.y);
		}

		//updating the editor camera;
		if(m_SceneViewportPanel.GetViewportFocused() && m_SceneViewportPanel.GetViewportHovered())
			m_EditorCamera.OnUpdate(dt);

		//Dark::Renderer2D::ResetStats();

		m_Framebuffer->Bind();

		Dark::Renderer::Clear({ 0.1f, 0.1f, 0.1f, 1.0f });

		// Updatting and Rendering the Scene
		m_ActiveScene->OnUpdateEditor(dt, m_EditorCamera);

		m_Framebuffer->UnBind();
	}

	void UltraEditorLayer::OnImGuiRender()
	{

		static bool dockspaceOpen{ true };
		static bool opt_fullscreen_persistant{ true };
		bool opt_fullscreen = opt_fullscreen_persistant;
		static ImGuiDockNodeFlags dockspace_flags{ ImGuiDockNodeFlags_None };

		ImGuiWindowFlags window_flags{ ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking };
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace", &dockspaceOpen, window_flags); //begining dockspace
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io{ ImGui::GetIO() };
		ImGuiStyle& style{ ImGui::GetStyle() };
		float minWinSizeX{ style.WindowMinSize.x };
		style.WindowMinSize.x = 200.0f;
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		style.WindowMinSize.x = minWinSizeX;

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("New", "Ctrl+N"))
					NewSceneFile();

				if (ImGui::MenuItem("Open...", "Ctrl+O"))
					OpenSceneFile();

				if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S"))
					SaveSceneFileAs();


				if (ImGui::MenuItem("Exit")) Dark::Application::Get().Close();

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Settings"))
			{
				if (ImGui::MenuItem("Editor Settings"))
					m_ShowEditorSettings = true;

				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		//editor settings menu imgui
		if(m_ShowEditorSettings)
			EditorSettingsMenu();

		//viewport
		m_SceneViewportPanel.OnImGuiRender(m_EditorCamera, m_Framebuffer, m_SceneHierarchyPanel.GetSelectedEntity());
		//scene hierarchy panel
		m_SceneHierarchyPanel.OnImGuiRender();

		//End of dockspace
		ImGui::End();
	}

	void UltraEditorLayer::EditorSettingsMenu()
	{
		if (ImGui::Begin("EditorSettings", &m_ShowEditorSettings))
		{

			if (ImGui::TreeNodeEx("Editor Camera", (ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick)))
			{

				//fov
				ImGui::Columns(2, "##Fov");
				ImGui::SetColumnWidth(0, 80.0f);
				ImGui::Text("Fov");
				ImGui::NextColumn();
				float cameraFov{ glm::degrees(m_EditorCamera.GetYFov()) };
				if (ImGui::DragFloat("##Fov", &cameraFov, 1.0f, 24.0f, 165.0f))
					m_EditorCamera.SetYFov(glm::radians(cameraFov));
				ImGui::Columns(1);

				//near clip
				ImGui::Columns(2, "##NearClip");
				ImGui::SetColumnWidth(0, 80.0f);
				ImGui::Text("NearClip");
				ImGui::NextColumn();
				float nearClip{ m_EditorCamera.GetNearClip() };
				if (ImGui::DragFloat("##NearClip", &nearClip, 0.1f, 0.00001f, 10000.0f))
					m_EditorCamera.SetNearClip(nearClip);
				ImGui::Columns(1);

				//far clip
				ImGui::Columns(2, "##FarClip");
				ImGui::SetColumnWidth(0, 80.0f);
				ImGui::Text("FarClip");
				ImGui::NextColumn();
				float farClip{ m_EditorCamera.GetFarClip() };
				if (ImGui::DragFloat("##FarClip", &farClip, 0.1f,0.00001f, 10000.0f))
					m_EditorCamera.SetFarClip(farClip);
				ImGui::Columns(1);

				//move speed
				ImGui::Columns(2, "##MoveSpeed");
				ImGui::SetColumnWidth(0, 80.0f);
				ImGui::Text("MoveSpeed");
				ImGui::NextColumn();
				float moveSpeed{ m_EditorCamera.GetMoveSpeed() };
				if (ImGui::DragFloat("##MoveSpeed", &moveSpeed, 0.1f, 1.0f, 24.0f))
					m_EditorCamera.SetMoveSpeed(moveSpeed);
				ImGui::Columns(1);

				//rotate speed
				ImGui::Columns(2, "##RotateSpeed");
				ImGui::SetColumnWidth(0, 80.0f);
				ImGui::Text("RotateSpeed");
				ImGui::NextColumn();
				float rotateSpeed{ m_EditorCamera.GetRotateSpeed() };
				if (ImGui::DragFloat("##RotateSpeed", &rotateSpeed, 1.0f, 1.0f, 180.0f))
					m_EditorCamera.SetRotateSpeed(rotateSpeed);
				ImGui::Columns(1);

				//zoom speed
				ImGui::Columns(2, "##ZoomSpeed");
				ImGui::SetColumnWidth(0, 80.0f);
				ImGui::Text("ZoomSpeed");
				ImGui::NextColumn();
				float zoomSpeed{ m_EditorCamera.GetZoomSpeed() };
				if (ImGui::DragFloat("##ZoomSpeed", &zoomSpeed, 1.0f, 1.0f, 24.0f))
					m_EditorCamera.SetZoomSpeed(zoomSpeed);
				ImGui::Columns(1);

				ImGui::TreePop();
			}

			//close button
			if (ImGui::Button("Close"))
				m_ShowEditorSettings = false;

		}
		ImGui::End();

	}

	//events
	void UltraEditorLayer::OnEvent(Event& e)
	{
		EventDispatcher dispatcher{ e };

		dispatcher.Dispatch<KeyPressedEvent>(DARK_BIND_EVENT_FN(UltraEditorLayer::OnKeyPressed));

		m_EditorCamera.OnEvent(e);
		m_SceneViewportPanel.OnEvent(e);
	}

	bool UltraEditorLayer::OnKeyPressed(KeyPressedEvent& e)
	{
		if (e.GetRepeatCount() > 0)
			return false;

		bool control{ Input::IsKeyPressed(KeyCode::KEY_LEFT_CONTROL) || Input::IsKeyPressed(KeyCode::KEY_RIGHT_CONTROL) };
		bool shift{ Input::IsKeyPressed(KeyCode::KEY_LEFT_SHIFT) || Input::IsKeyPressed(KeyCode::KEY_RIGHT_SHIFT) };

		switch (e.GetKeyCode())
		{
			//shortcut keys for scene loading/saving and stuff
			case KeyCode::KEY_N:
			{
				if (control)
					NewSceneFile();
				break;
			}

			case KeyCode::KEY_O:
			{
				if (control)
					OpenSceneFile();
				break;
			}

			case KeyCode::KEY_S:
			{
				if (control && shift)
					SaveSceneFileAs();
				break;
			}
		}

		return false;
	}

	//loading and saving scene helpers;
	void UltraEditorLayer::NewSceneFile()
	{
		m_ActiveScene = CreateRef<Scene>();
		const auto& viewportPanelSize{ m_SceneViewportPanel.GetViewportPanelSize() };
		m_ActiveScene->OnViewportResize((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y);
		m_SceneViewportPanel.SetContext(m_ActiveScene);
		m_SceneHierarchyPanel.SetContext(m_ActiveScene);
	}

	void UltraEditorLayer::OpenSceneFile()
	{
		std::string filePath{ FileDialogs::OpenFile("Dark Scene (*.dscn)\0*.dscn\0") };

		if (!filePath.empty())
		{
			m_ActiveScene = CreateRef<Scene>();
			const auto& viewportPanelSize{ m_SceneViewportPanel.GetViewportPanelSize() };
			m_ActiveScene->OnViewportResize((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y);
			m_SceneViewportPanel.SetContext(m_ActiveScene);
			m_SceneHierarchyPanel.SetContext(m_ActiveScene);

			SceneSerializer serializer{ m_ActiveScene };
			serializer.Deserialize(filePath);
		}
	}

	void UltraEditorLayer::SaveSceneFileAs()
	{
		std::string filePath{ FileDialogs::SaveFile("Dark Scene (*.dscn)\0*.dscn\0") };

		if (!filePath.empty())
		{
			SceneSerializer serializer{ m_ActiveScene };
			serializer.Serialize(filePath);
		}
	}
}