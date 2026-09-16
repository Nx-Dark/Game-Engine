#include "SandBox2D.h"

SandBox2D::SandBox2D()
	: Layer("SandBox2D"), m_CameraController{ 960.0f / 540.0f, 2.0f, 45.0f }
{

}

void SandBox2D::OnAttach()
{
	DARK_PROFILE_FUNCTION();

	m_Rect = {
		glm::vec2{ 0.0f, 0.0f },
		glm::vec2{ 2.0f, 2.0f },
		glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }
	};

	m_TexRect = {
		glm::vec2{ 1.5f, 0.0f },
		glm::vec2{ 3.0f, 3.0f }
	};

	m_TexRect_2 = {
		glm::vec2{ -5.0f, -5.0f },
		glm::vec2{ 1.0f, 1.0f }
	};

	m_Texture = Dark::Texture2D::Create("Assets/Textures/adawong.jpg");

}

void SandBox2D::OnDetach()
{
	DARK_PROFILE_FUNCTION();

}

void SandBox2D::OnUpdate(Dark::DeltaTime dt)
{

	DARK_PROFILE_FUNCTION();
	

	m_CameraController.OnUpdate(dt);

	Dark::Renderer2D::ResetStats();

	Dark::RenderCommand::Clear({ 0.0f, 0.0f, 0.0f, 1.0f });

	Dark::Renderer2D::BeginScene(m_CameraController.GetCamera());

	Dark::Renderer2D::DrawQuad(m_TexRect, m_Texture, glm::vec4{1.0f}, 10.0f);
	Dark::Renderer2D::DrawRotatedQuad(m_TexRect_2, m_Texture, glm::radians(m_Angle), glm::vec4{ 1.0f }, 2.0f);

	for (float y{-5.0f}; y < 5.0f; y+=0.5f) {
		for (float x{-5.0f}; x < 5.0f; x+=0.5f) {
			Dark::ColorRect rect{
				glm::vec2{float(x), float(y)},
				glm::vec2{0.45f, 0.45f},
				glm::vec4{(x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.5f }
			};
			Dark::Renderer2D::DrawQuad(rect, 0.1);
		}
	}

	Dark::Renderer2D::EndScene();

}

void SandBox2D::OnEvent(Dark::Event& e)
{
	m_CameraController.OnEvent(e);
}

void SandBox2D::OnImGuiRender()
{
	DARK_PROFILE_FUNCTION();

	ImGui::Begin(m_Name.c_str());

		auto stats{ Dark::Renderer2D::GetStats() };

		ImGui::Text("Renderer2D Stats: ");	
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.GetQuadCount());
		ImGui::Text("Vertices: %d", stats.GetQuadVertexCount());
		ImGui::Text("Indices: %d", stats.GetQuadIndexCount());
		ImGui::Text("Triangles: %d", stats.GetQuadTriangleCount());

		ImGui::DragFloat2("Texture Pos", &m_TexRect.position.x, 0.05f);
		ImGui::DragFloat("Angle", &m_Angle, 0.1f);

	ImGui::End(); 
}
