#include "ParticleSystem.h"
#include "Random.h"

#include "glm/gtc/constants.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/compatibility.hpp"

ParticleSystem::ParticleSystem(uint32_t maxParticles)
	: m_ParticlePoolIndex{ maxParticles - 1 }
{
	m_ParticlePool.resize(maxParticles);
}

void ParticleSystem::OnUpdate(Dark::DeltaTime dt)
{
	for (auto& particle : m_ParticlePool)
	{
		if (!particle.Active) continue;

		if (particle.lifeRemaining <= 0.0f) {
			particle.Active = false;
			continue;
		}

		particle.lifeRemaining -= dt;
		particle.Position += particle.Velocity * (float)dt;
		particle.Rotation += 0.01f * dt;

	}
}

void ParticleSystem::OnRender()
{

	for (auto& particle : m_ParticlePool)
	{
		if (!particle.Active)
			continue;

		float life{ particle.lifeRemaining / particle.lifeTime };
		glm::vec4 color{ glm::lerp(particle.colorEnd, particle.colorBegin, life) };

		float size{ glm::lerp(particle.sizeEnd, particle.sizeBegin, life) };

		Dark::ColorRect particle_rect{
			particle.Position,
			{size, size},
			color
		};

		Dark::Renderer2D::DrawRotatedQuad(particle_rect, particle.Rotation);
	}

}

void ParticleSystem::OnRender(const Dark::Ref<Dark::Texture2D>& texture) 
{
	for (auto& particle : m_ParticlePool)
	{
		if (!particle.Active)
			continue;

		float life{ particle.lifeRemaining / particle.lifeTime };
		glm::vec4 color{ 1.0f, 1.0f, 1.0f, glm::lerp(0.0f, 1.0f, life) };

		float size{ glm::lerp(particle.sizeEnd, particle.sizeBegin, life) };

		Dark::Renderer2D::DrawRotatedQuad(particle.Position, {size, size}, texture, particle.Rotation, color);
	}
}

void ParticleSystem::OnRender(const Dark::Ref<Dark::SubTexture2D>& subTexture)
{
	for (auto& particle : m_ParticlePool)
	{
		if (!particle.Active)
			continue;

		float life{ particle.lifeRemaining / particle.lifeTime };
		glm::vec4 color{ 1.0f, 1.0f, 1.0f, glm::lerp(0.0f, 1.0f, life) };

		float size{ glm::lerp(particle.sizeEnd, particle.sizeBegin, life) };

		Dark::Renderer2D::DrawRotatedQuad(particle.Position, {size, size}, subTexture, particle.Rotation, color);
	}
}

void ParticleSystem::Emit(const ParticleProps& particleProps)
{
	Particle& particle{ m_ParticlePool[m_ParticlePoolIndex] };
	particle.Active = true;
	particle.Position = particleProps.Position;
	particle.Rotation = Random::Float() * 2.0f * glm::pi<float>();

	//velocity
	particle.Velocity = particleProps.Velocity;
	particle.Velocity.x += particleProps.VelocityVariation.x * (Random::Float() - 0.5f);
	particle.Velocity.y += particleProps.VelocityVariation.y * (Random::Float() - 0.5f);

	//color
	particle.colorBegin = particleProps.colorBegin;
	particle.colorEnd = particleProps.colorEnd;

	particle.lifeTime = particleProps.lifeTime;
	particle.lifeRemaining = particleProps.lifeTime;

	//size
	particle.sizeBegin = particleProps.sizeBegin + particleProps.sizeVariation * (Random::Float() - 0.5f);
	particle.sizeEnd = particleProps.sizeEnd;

	m_ParticlePoolIndex = --m_ParticlePoolIndex % m_ParticlePool.size(); //keeps it b/w 0 and 1000(exclusive)
}