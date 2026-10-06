#include "dpch.h"
#include "Scene.h"

#include <glm/glm.hpp>

#include "Dark/Scene/Components.h"

#include "Dark/Renderer/Renderer2D.h"

namespace Dark
{

	Scene::Scene()
	{


	}

	Scene::~Scene()
	{

	}

	entt::entity Scene::CreateEntity()
	{
		return m_Registry.create();
	}

	void Scene::OnUpdate(DeltaTime dt)
	{
		auto group{ m_Registry.group<TransformComponent, SpriteRendererComponent>() };
		for (entt::entity entity : group)
		{
			auto [transform, sprtieRenderer] { group.get<TransformComponent, SpriteRendererComponent>(entity) };

			Renderer2D::DrawQuad(transform, sprtieRenderer.Color);
		}
	}

}