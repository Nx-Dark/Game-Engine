#include "dpch.h"
#include "Scene.h"
#include "Entity.h"

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

	void Scene::OnUpdate(DeltaTime dt)
	{
		auto group{ m_Registry.group<TransformComponent, SpriteRendererComponent>() };
		for (entt::entity entity : group)
		{
			auto&& [transform, sprtieRenderer] { group.get<TransformComponent, SpriteRendererComponent>(entity) };

			Renderer2D::DrawQuad(transform, sprtieRenderer.Color);
		}
	}
	
	//Creating the 
	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity e{ m_Registry.create(), this };
		e.AddComponent<TransformComponent>();
		TagComponent& tag{ e.AddComponent<TagComponent>() };
		tag.Tag = name.empty() ? "Entity" : name;
		return e;
	}

}