#pragma once

#include "Dark.h"

class SandBox2D : public Dark::Layer
{

private:
	//camera
	Dark::OrthoGraphicCameraController m_CameraController;
	
	Dark::Ref<Dark::Texture2D> m_Texture{};

	Dark::Ref<Dark::ColorRect> m_Rect{};
	Dark::Ref<Dark::Rect> m_TexRect{};

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