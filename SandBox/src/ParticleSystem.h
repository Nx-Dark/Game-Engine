#pragma once

#include <Dark.h>

struct ParticleProps
{
	glm::vec2 Position{};
	glm::vec2 Velocity{}, VelocityVariation{};
	glm::vec4 colorBegin{}, colorEnd{};
	float sizeBegin{}, sizeEnd{}, sizeVariation{};
	float lifeTime{ 1.0f };
};

class ParticleSystem
{

	struct Particle
	{
		glm::vec2 Position{};
		glm::vec2 Velocity{};
		glm::vec4 colorBegin{}, colorEnd{};
		float Rotation = 0.0f;
		float sizeBegin{}, sizeEnd{};

		float lifeTime{ 1.0f };
		float lifeRemaining{ 0.0f };

		bool Active{ false };

		Particle() = default;
	};

	std::vector<Particle> m_ParticlePool;
	uint32_t m_ParticlePoolIndex{};

public:
	ParticleSystem(uint32_t maxParticles = 1000u);

	void OnUpdate(Dark::DeltaTime dt);
	void OnRender();
	void OnRender(const Dark::Ref<Dark::Texture2D>& texture);
	void OnRender(const Dark::Ref<Dark::SubTexture2D>& subtexture);

	void Emit(const ParticleProps& particleProps);
};