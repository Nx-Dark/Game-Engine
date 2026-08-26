#include "SandBox2D.h"

#include "Platform/OpenGL/OpenGLShader.h"

SandBox2D::SandBox2D()
	: Layer("SandBox2D"), m_CameraController{ 960.0f / 540.0f, 2.0f, 45.0f }
{

}

void SandBox2D::OnAttach()
{
}

void SandBox2D::OnDetach()
{
}

void SandBox2D::OnUpdate(Dark::DeltaTime dt)
{
	m_CameraController.OnUpdate(dt);

	Dark::RenderCommand::Clear({ 0.0f, 0.0f, 0.0f, 1.0f });
	
	Dark::Renderer2D::BeginScene(m_CameraController.GetCamera());

	Dark::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, m_Color);

	Dark::Renderer2D::EndScene();
}

void SandBox2D::OnEvent(Dark::Event& e)
{
	m_CameraController.OnEvent(e);
}

void SandBox2D::OnImGuiRender()
{
	ImGui::Begin(m_Name.c_str());;

		ImGui::ColorEdit4("Tile Color", glm::value_ptr(m_Color));

	ImGui::End();
}
