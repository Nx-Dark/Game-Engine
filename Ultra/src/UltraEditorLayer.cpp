#include "UltraEditorLayer.h"

namespace Dark {

	static const uint32_t s_TileMapWidth{ 24 };
	static const uint32_t s_TileMapHeight{ 16 };
	static const char* s_TileMap
	{
	"WWWWWWWWWDDDDDWWWWWWWWWW"
	"WWWWWWWDDDDDDDDDWWWWWWWW"
	"WWWWWDDDDDDDDDDDDDWWWWWW"
	"WWWDDDDDDDDDDDDDDDDDWWWW"
	"WDDDDDDDDDDDDDWWWDDDWWWW"
	"WWWDDDDDDDDDDDWWWDDDWWWW"
	"WWWWWDDDDDDDDDDDDDDWWWWW"
	"WWWWWWWDDDDDDDDDDDDWWWWW"
	"WWWWWWWDDDDDDWWDDDDWWWWW"
	"WWWWWWWWWDDDDWWDDDWWWWWW"
	"WWWWWWWWWWWDDDDDDWWWWWWW"
	"WWWWWWWWWWWWWDDDDWWWWWWW"
	"WWWWWWWWWWWWWWWWWWWWWWWW"
	"WWWWWWWWWWWWWWWWWWWWWWWW"
	"WWWWWWWWWWWWWWWWWWWWWWWW"
	"WWWWWWWWWWWWWWWWWWWWWWWW"
	};

	UltraEditorLayer::UltraEditorLayer()
		: Layer("UltraEditorLayer")
	{
	}

	UltraEditorLayer::~UltraEditorLayer()
	{

	}

	void UltraEditorLayer::OnAttach()
	{

		m_SpriteSheet = Dark::Texture2D::Create("Assets/Textures/tilemap_packed.png");
		m_TileHashMap['D'] = Dark::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 1, 16 }, { 16, 16 });
		m_TileHashMap['W'] = Dark::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 9, 10 }, { 16, 16 });

		//framebuffer
		Dark::FramebufferSpecifications fbSpec;
		fbSpec.Width = Dark::Application::Get().GetWindow().GetWidth();
		fbSpec.Height = Dark::Application::Get().GetWindow().GetHeight();
		m_Framebuffer = Dark::Framebuffer::Create(fbSpec);

		m_Music = Dark::AudioData::Create("Assets/audio/music.mp3", Dark::AudioFlag::FLAG_STREAM);
		//m_Music->PlayAudio();

		//active scene
		m_ActiveScene = CreateRef<Scene>();

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

		//panels
		m_SceneHierarchyPanel.SetContext(m_ActiveScene);

	}

	void UltraEditorLayer::OnDetach()
	{

	}

	void UltraEditorLayer::OnEvent(Dark::Event& e)
	{
		
	}

	void UltraEditorLayer::OnUpdate(Dark::DeltaTime dt)
	{

		//resizing the framebuffer and the viewport panel
		if (auto frameBufferSpec{ m_Framebuffer->GetSpecifications() };
			m_ViewportPanelSize.x != 0.0f && m_ViewportPanelSize.y != 0.0f
			&& (frameBufferSpec.Width != m_ViewportPanelSize.x || frameBufferSpec.Height != m_ViewportPanelSize.y))
		{
			m_Framebuffer->ReSize((uint32_t)m_ViewportPanelSize.x, (uint32_t)m_ViewportPanelSize.y);

			//resizing the viewport of the current active scene;
			m_ActiveScene->OnViewportResize((uint32_t)m_ViewportPanelSize.x, (uint32_t)m_ViewportPanelSize.y);
		}

		//Rendering stuff
		Dark::Renderer2D::ResetStats();

		m_Framebuffer->Bind();

		Dark::Renderer::Clear({ 0.1f, 0.1f, 0.1f, 1.0f });

		// Updatting and Rendering the Scene
		m_ActiveScene->OnUpdate(dt);

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
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{

				if (ImGui::MenuItem("Exit")) Dark::Application::Get().Close();
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		ImGui::Begin("Stats");
			auto stats = Dark::Renderer2D::GetStats();
			ImGui::Text("Stats:");
			ImGui::Text("Draw Calls: %d", stats.DrawCalls);
			ImGui::Text("Quads: %d", stats.QuadCount);
			ImGui::Text("Vertices: %d", stats.GetQuadVertexCount());
			ImGui::Text("Indices: %d", stats.GetQuadIndexCount());

		ImGui::End();
		

		//viewport and framebuffer bullshit
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.0f, 0.0f });
		ImGui::Begin("Viewport");

			//if the viewport is focused or hovered
			m_ViewportFocused = ImGui::IsWindowFocused();
			m_ViewportHovered = ImGui::IsWindowHovered();
			Application::Get().GetImGuiLayer()->AllowEvents(m_ViewportFocused && m_ViewportHovered);

			ImVec2 viewportPanelSize{ ImGui::GetContentRegionAvail() };

			if (m_ViewportPanelSize != glm::vec2{ viewportPanelSize.x, viewportPanelSize.y }) {
				m_ViewportPanelSize = { viewportPanelSize.x, viewportPanelSize.y };
			}

			ImGui::Image((void*)m_Framebuffer->GetColorAttachmentRendererID(), viewportPanelSize, { 0.0f, 1.0f }, { 1.0f, 0.0f });

		ImGui::End();
		ImGui::PopStyleVar();

		//scene hierarchy panel
		m_SceneHierarchyPanel.OnImGuiRender();

		//End of dockspace
		ImGui::End();
	}
}