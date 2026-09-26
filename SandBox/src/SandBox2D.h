#pragma once

#include <Dark.h>

#include "ParticleSystem.h"

class SandBox2D : public Dark::Layer
{	

private:

	ParticleSystem m_ParticleSystem;
	ParticleProps m_Particle;

	Dark::Ref<Dark::Texture2D> m_Texture;

	Dark::OrthoGraphicCameraController m_Camera;

public:
	SandBox2D();
	virtual ~SandBox2D();

	void OnAttach() override;
	void OnDetach() override;

	void OnUpdate(Dark::DeltaTime dt) override;
	void OnEvent(Dark::Event& e) override;
	
	void OnImGuiRender() override;

};