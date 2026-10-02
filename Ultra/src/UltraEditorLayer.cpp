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
		: Layer("UltraEditorLayer"), m_Camera(
			(float)Application::Get().GetWindow().GetWidth() / (float)Application::Get().GetWindow().GetHeight(),
			0.1f, 0.1f)
	{
	}

	UltraEditorLayer::~UltraEditorLayer()
	{

	}

	void UltraEditorLayer::OnAttach()
	{

		m_Camera.SetZoomLevel(2.0f);

		m_SpriteSheet = Dark::Texture2D::Create("Assets/Textures/tilemap_packed.png");
		m_TileHashMap['D'] = Dark::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 1, 16 }, { 16, 16 });
		m_TileHashMap['W'] = Dark::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 9, 10 }, { 16, 16 });

		//framebuffer
		Dark::FramebufferSpecifications fbSpec;
		fbSpec.Width = Dark::Application::Get().GetWindow().GetWidth();
		fbSpec.Height = Dark::Application::Get().GetWindow().GetHeight();
		m_Framebuffer = Dark::Framebuffer::Create(fbSpec);

		m_Music = Dark::AudioData::Create("Assets/audio/music.mp3", Dark::AudioFlag::FLAG_STREAM);
		m_Music->PlayAudio();
	}

	void UltraEditorLayer::OnDetach()
	{

	}

	void UltraEditorLayer::OnEvent(Dark::Event& e)
	{
		m_Camera.OnEvent(e);
	}

	void UltraEditorLayer::OnUpdate(Dark::DeltaTime dt)
	{

		static float musicTime{ 0.0f };
		musicTime += dt;

		if (musicTime >= 10.0f && m_Music->isAudioPlaying()) m_Music->StopAudio();

		//camera Update
		m_Camera.OnUpdate(dt);

		//Rendering stuff
		Dark::Renderer2D::ResetStats();

		m_Framebuffer->Bind();

		Dark::Renderer::Clear({ 0.1f, 0.1f, 0.1f, 1.0f });

		Dark::Renderer2D::BeginScene(m_Camera.GetCamera());

		for (uint32_t y{}; y < s_TileMapHeight; y++)
		{
			for (uint32_t x{}; x < s_TileMapWidth; x++)
			{
				const char tileC{ s_TileMap[(y * s_TileMapWidth) + x] };

				if (m_TileHashMap.contains(tileC))
				{
					Dark::Renderer2D::DrawQuad({ {x - s_TileMapWidth / 2.0f,  s_TileMapHeight - y - s_TileMapHeight / 2.0f} }, m_TileHashMap[tileC]);
				}
			}
		}

		Dark::Renderer2D::EndScene();

		m_Framebuffer->UnBind();
	}

	void UltraEditorLayer::OnImGuiRender()
	{

		static bool dockingEnabled{ true };
		if (dockingEnabled)
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
			ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
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

				auto stats = Dark::Renderer2D::GetStats();
				ImGui::Text("Renderer2D Stats:");
				ImGui::Text("Draw Calls: %d", stats.DrawCalls);
				ImGui::Text("Quads: %d", stats.QuadCount);
				ImGui::Text("Vertices: %d", stats.GetQuadVertexCount());
				ImGui::Text("Indices: %d", stats.GetQuadIndexCount());
				ImGui::EndMenuBar();
			}

			ImGui::Begin("Settings");

			auto stats = Dark::Renderer2D::GetStats();
			ImGui::Text("Renderer2D Stats:");
			ImGui::Text("Draw Calls: %d", stats.DrawCalls);
			ImGui::Text("Quads: %d", stats.QuadCount);
			ImGui::Text("Vertices: %d", stats.GetQuadVertexCount());
			ImGui::Text("Indices: %d", stats.GetQuadIndexCount());

			ImGui::Image((void*)m_Framebuffer->GetColorAttachmentRendererID(), ImVec2{ 960.0f, 540.0f }, ImVec2{ 0.0f, 1.0f }, ImVec2{ 1.0f, 0.0f });
			ImGui::End();

			ImGui::End();
		}
		else
		{
			ImGui::Begin("Settings");

			auto stats = Dark::Renderer2D::GetStats();
			ImGui::Text("Renderer2D Stats:");
			ImGui::Text("Draw Calls: %d", stats.DrawCalls);
			ImGui::Text("Quads: %d", stats.QuadCount);
			ImGui::Text("Vertices: %d", stats.GetQuadVertexCount());
			ImGui::Text("Indices: %d", stats.GetQuadIndexCount());

			ImGui::Image((void*)m_Framebuffer->GetColorAttachmentRendererID(), ImVec2{ 960.0f, 540.0f }, ImVec2{ 0.0f, 1.0f }, ImVec2{ 1.0f, 0.0f });
			ImGui::End();
		}
	}
}