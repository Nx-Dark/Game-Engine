#pragma once

#include <Dark.h>

#include "ParticleSystem.h"

class SandBox2D : public Dark::Layer
{	

private:

	ParticleSystem m_ParticleSystem;
	ParticleProps m_Particle;

	Dark::Ref<Dark::Texture2D> m_SpriteSheet;
	Dark::Ref<Dark::Framebuffer> m_Framebuffer;

	Dark::OrthoGraphicCameraController m_Camera;

	std::unordered_map<char, Dark::Ref<Dark::SubTexture2D>> m_TileHashMap;

public:
	SandBox2D();
	virtual ~SandBox2D();

	void OnAttach() override;
	void OnDetach() override;

	void OnUpdate(Dark::DeltaTime dt) override;
	void OnEvent(Dark::Event& e) override;
	
	void OnImGuiRender() override;

};