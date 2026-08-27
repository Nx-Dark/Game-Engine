#pragma once

#include "Dark.h"

class SandBox2D : public Dark::Layer
{

private:
	//camera
	Dark::OrthoGraphicCameraController m_CameraController;
	
	Dark::Ref<Dark::Texture2D> m_Texture{};

	glm::vec2 m_Pos{ 0.0f };
	glm::vec2 m_Size{ 1.0f };
	glm::vec4 m_Color{ 0.0f, 0.0f, 1.0f, 1.0f };
	glm::vec4 m_TintColor{ 1.0f };
	float m_Angle{};
public:
	SandBox2D();
	virtual ~SandBox2D() = default;

	void OnAttach() override;
	void OnDetach() override;

	void OnUpdate(Dark::DeltaTime dt) override;

	void OnEvent(Dark::Event& e) override;

	void OnImGuiRender() override;

};