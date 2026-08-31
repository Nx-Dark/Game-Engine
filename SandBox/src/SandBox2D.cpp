#include "SandBox2D.h"

#define SCOPE_PROFILE(name) Dark::ProfilingTimer profTimer##__LINE__(name, [&](SandBox2D::ProfileResult profileResult) { m_ProfileResults.push_back(profileResult); })

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
	DARK_PROFILE_SCOPE("Render Draw");
	Dark::Renderer2D::DrawRotatedQuad(m_TexRect, m_Texture, glm::radians(m_Angle), m_TintColor, 10.0f);
	Dark::Renderer2D::DrawQuad(m_Rect);
	Dark::Renderer2D::DrawRotatedQuad(m_Rect, glm::radians(45.0f));

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

		ImGui::InputFloat2("Position", glm::value_ptr(m_TexRect->position));
		ImGui::InputFloat2("Size", glm::value_ptr(m_TexRect->size));
		ImGui::ColorEdit4("Tint", glm::value_ptr(m_TintColor));
		ImGui::InputFloat("Angle", &m_Angle);

	ImGui::End();
}
