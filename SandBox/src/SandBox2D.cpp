#include "SandBox2D.h"

#define SCOPE_PROFILE(name) Dark::ProfilingTimer profTimer##__LINE__(name, [&](SandBox2D::ProfileResult profileResult) { m_ProfileResults.push_back(profileResult); })

SandBox2D::SandBox2D()
	: Layer("SandBox2D"), m_CameraController{ 960.0f / 540.0f, 2.0f, 45.0f }
{

}

void SandBox2D::OnAttach()
{

	m_Texture = Dark::Texture2D::Create("Assets/Textures/adawong.jpg");

}

void SandBox2D::OnDetach()
{
}

void SandBox2D::OnUpdate(Dark::DeltaTime dt)
{

	SCOPE_PROFILE("SandBox2D::OnUpdate");
	
{
	SCOPE_PROFILE("CameraController::OnUpdate");
	m_CameraController.OnUpdate(dt);
}

{
	SCOPE_PROFILE("Render Prep");
	Dark::RenderCommand::Clear({ 0.0f, 0.0f, 0.0f, 1.0f });
	Dark::Renderer2D::BeginScene(m_CameraController.GetCamera());
}

{
	SCOPE_PROFILE("Render Draw");
	Dark::Renderer2D::DrawQuad(m_Pos, m_Size, m_Texture, m_TintColor, m_Angle);
	Dark::Renderer2D::DrawQuad({ 1.5f, 0.0f, 0.1f }, m_Size, m_Color);

	Dark::Renderer2D::EndScene();
}

}

void SandBox2D::OnEvent(Dark::Event& e)
{
	m_CameraController.OnEvent(e);
}

void SandBox2D::OnImGuiRender()
{
	ImGui::Begin(m_Name.c_str());;

		ImGui::ColorEdit4("Tile Color", glm::value_ptr(m_Color));
		ImGui::InputFloat2("Position", glm::value_ptr(m_Pos));
		ImGui::InputFloat2("Size", glm::value_ptr(m_Size));
		ImGui::ColorEdit4("Tint", glm::value_ptr(m_TintColor));
		ImGui::InputFloat("Angle", &m_Angle);

		for (auto& pr : m_ProfileResults)
		{
			char buff[50];
			strcpy(buff, "%.3fms  ");
			strcat(buff, pr.name);
			ImGui::Text(buff, pr.duration);
		}

		m_ProfileResults.clear();

	ImGui::End();
}
