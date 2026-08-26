#pragma once

#include "Dark.h"

class SandBox2D : public Dark::Layer
{

private:
	Dark::Ref<Dark::VertexArray> m_VertexArray{};
	Dark::Ref<Dark::Shader> m_Shader{};

	//camera
	Dark::OrthoGraphicCameraController m_CameraController;
	//color vectors for the squares
	glm::vec4 m_Color{ 0.0f, 0.0f, 1.0f, 1.0f };

public:
	SandBox2D();
	virtual ~SandBox2D() = default;

	void OnAttach() override;
	void OnDetach() override;

	void OnUpdate(Dark::DeltaTime dt) override;

	void OnEvent(Dark::Event& e) override;

	void OnImGuiRender() override;

};