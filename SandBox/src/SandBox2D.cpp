#include "SandBox2D.h"

SandBox2D::SandBox2D()
	: Layer("SandBox2D"), m_CameraController{ 960.0f / 540.0f, 2.0f, 45.0f }
{

}

void SandBox2D::OnAttach()
{
	DARK_PROFILE_FUNCTION();

	m_Rect = Dark::CreateRef<Dark::ColorRect>(
		glm::vec2{ -1.0f, 0.0f },
		glm::vec2{ 2.0f, 2.0f },
		glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }
	);

	m_TexRect = Dark::CreateRef<Dark::Rect>(
		glm::vec2{ 1.5f, 0.0f },
		glm::vec2{ 3.0f, 3.0f }
	);

	m_TexRect_2 = Dark::CreateRef<Dark::Rect>(
		glm::vec2{ -5.0f, -5.0f },
		glm::vec2{ 1.0f, 1.0f }
	);

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

{
	DARK_PROFILE_SCOPE("Render Prep");
	Dark::RenderCommand::Clear({ 0.0f, 0.0f, 0.0f, 1.0f });
	Dark::Renderer2D::BeginScene(m_CameraController.GetCamera());
}

{
	m_Rect->color = glm::vec4{ 1.0f, 0.4f, 0.1f, 1.0f };
	m_Rect->position = glm::vec2{ 2.0f, 2.0f };
	Dark::Renderer2D::DrawQuad(m_Rect);
	m_Rect->color = glm::vec4{ 0.5f, 0.2f, 0.6f, 1.0f };
	m_Rect->position = glm::vec2{ -1.0f, -1.0f };
	Dark::Renderer2D::DrawQuad(m_Rect);

	Dark::Renderer2D::DrawQuad(m_TexRect, m_Texture, glm::vec4{1.0f}, 10.0f);
	Dark::Renderer2D::DrawQuad(m_TexRect_2, m_Texture, glm::vec4{ 1.0f }, 2.0f);

	Dark::Renderer2D::EndScene();
}

}

void SandBox2D::OnEvent(Dark::Event& e)
{
	m_CameraController.OnEvent(e);
}

void SandBox2D::OnImGuiRender()
{
	DARK_PROFILE_FUNCTION();

	ImGui::Begin(m_Name.c_str());;

		ImGui::DragFloat2("Texture Pos", &m_TexRect->position.x, 0.05f);

	ImGui::End(); 
}
