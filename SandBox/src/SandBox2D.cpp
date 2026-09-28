#include "SandBox2D.h"
#include "ParticleSystem.h"

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

SandBox2D::SandBox2D()
	: Layer("SandBox2D"), m_Camera(16.0f / 9.0f, 0.1f, 0.1f), m_ParticleSystem{ 1000u }
{
}

SandBox2D::~SandBox2D()
{

}

void SandBox2D::OnAttach()
{
	m_Particle.Velocity = { 0.5f, 0.5f };
	m_Particle.VelocityVariation = { 0.2f, 0.1f };
	m_Particle.colorBegin = { 0.5f, 0.2f, 0.3f, 1.0f };
	m_Particle.colorEnd = { 0.2, 0.5f, 0.6f, 0.0f };
	m_Particle.sizeBegin = 0.4f;
	m_Particle.sizeEnd = 0.05f;
	m_Particle.sizeVariation = 0.15f;
	m_Particle.lifeTime = 5.0f;

	m_Camera.SetZoomLevel(2.0f);

	m_SpriteSheet = Dark::Texture2D::Create("Assets/Game/Textures/tilemap_packed.png");
	m_TileHashMap['D'] = Dark::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 1, 16 }, { 16, 16 });
	m_TileHashMap['W'] = Dark::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 9, 10 }, { 16, 16 });
}

void SandBox2D::OnDetach()
{

}

void SandBox2D::OnEvent(Dark::Event& e)
{
	m_Camera.OnEvent(e);
}

void SandBox2D::OnUpdate(Dark::DeltaTime dt)
{

	//emitting particle based on mouse position and click
	if (Dark::Input::IsMouseButtonPressed(DK_MOUSE_BUTTON_1)) {

		auto [x, y] { Dark::Input::GetMousePos() };
		uint32_t width{ Dark::Application::Get().GetWindow().GetWidth() };
		uint32_t height{ Dark::Application::Get().GetWindow().GetHeight() };

		auto camBounds{ m_Camera.GetBounds() };
		auto camPos{ m_Camera.GetCamera().GetPosition() };

		x = (x / (float)width) * camBounds.GetWidth() - camBounds.GetWidth() * 0.5f;
		y = camBounds.GetHeight() * 0.5f - (y / (float)height) * camBounds.GetHeight();

		m_Particle.Position = { x + camPos.x, y + camPos.y };

		for (int i{}; i < 20; i++) {
			m_ParticleSystem.Emit(m_Particle);
		}

	}

	//camera Update
	m_Camera.OnUpdate(dt);

	m_ParticleSystem.OnUpdate(dt);

	//Rendering stuff
	Dark::Renderer2D::ResetStats();

	Dark::RenderCommand::Clear({ 0.5f, 0.0f, 0.0f, 1.0f });

	Dark::Renderer2D::BeginScene(m_Camera.GetCamera());

	//rendering particles
	m_ParticleSystem.OnRender();

	//Dark::Renderer2D::DrawQuad({}, m_GrassTile_left);
	//Dark::Renderer2D::DrawQuad({ {1.0f, 0.0f} }, m_GrassTile_mid);

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
}

void SandBox2D::OnImGuiRender()
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

		ImGui::Image((void*)m_SpriteSheet->GetRendererID(), ImVec2{ 256.0f, 256.0f });
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

		ImGui::Image((void*)m_SpriteSheet->GetRendererID(), ImVec2{256.0f, 256.0f});
		ImGui::End();
	}
}