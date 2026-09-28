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

	static bool dockspaceOpen{ true };
	static ImGuiDockNodeFlags  DockSpaceFlags = ImGuiDockNodeFlags_None;

	ImGui::DockSpaceOverViewport(0, nullptr, DockSpaceFlags);

	if (ImGui::BeginMenuBar()) {
		if (ImGui::BeginMenu("Sys")) {

			if (ImGui::MenuItem("Exit")) Dark::Application::Get().Close();

			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}

	const auto& stats{ Dark::Renderer2D::GetStats() };

	ImGui::Begin("SandBox2D");
	ImGui::Text("DrawCalls: %d", stats.DrawCalls);
	ImGui::Text("QuadCount: %d", stats.QuadCount);
	ImGui::DragFloat2("ParticleVel", &m_Particle.Velocity.x, 0.1f);
	ImGui::DragFloat2("ParticleVelVar", &m_Particle.VelocityVariation.x, 0.1f);

	ImGui::Image((void*)m_SpriteSheet->GetRendererID(), ImVec2{ 64.0f, 64.0f });

	ImGui::End();
}