#include "SandBox2D.h"
#include "ParticleSystem.h"

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
	m_Particle.sizeBegin = 0.2f;
	m_Particle.sizeEnd = 0.05f;
	m_Particle.sizeVariation = 0.15f;
	m_Particle.lifeTime = 5.0f;

	m_SpriteSheet = Dark::Texture2D::Create("Assets/Game/Textures/tilemap_packed.png");
	m_TrafficLightTexture = Dark::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 4, 2 }, { 16, 16 });
	m_BarrelTex = Dark::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 9, 8 }, { 16, 16 });
	m_TreeTex = Dark::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 17, 8 }, { 16, 16 }, { 1, 2 });
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
	m_ParticleSystem.OnRender(m_BarrelTex);

	Dark::Renderer2D::DrawQuad({}, m_TrafficLightTexture);
	Dark::Renderer2D::DrawQuad({ { 0.7f, 0.0f } }, m_BarrelTex);
	Dark::Renderer2D::DrawQuad({ { 2.0f, 0.0f }, { 1.0f, 2.0f } }, m_TreeTex);

	Dark::Renderer2D::EndScene();
}

void SandBox2D::OnImGuiRender()
{

	const auto& stats{ Dark::Renderer2D::GetStats() };

	ImGui::Begin("SandBox2D");
	ImGui::Text("DrawCalls: %d", stats.DrawCalls);
	ImGui::Text("QuadCount: %d", stats.QuadCount);
	ImGui::DragFloat2("ParticleVel", &m_Particle.Velocity.x, 0.1f);
	ImGui::DragFloat2("ParticleVelVar", &m_Particle.VelocityVariation.x, 0.1f);
	ImGui::End();

}