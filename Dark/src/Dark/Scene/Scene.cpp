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

	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		m_ViewportWidth = width;
		m_ViewportHeight = height;

		//setting the projection of the non fixed aspect ratio camera components
		{
			auto view{ m_Registry.view<CameraComponent>() };
			for (auto entity : view)
			{
				auto& cameraComp{ view.get<CameraComponent>(entity) };
				if (!cameraComp.FixedAspectRatio) {
					cameraComp.Camera.SetViewportSize(width, height);
				}
			}
		}
	}

	void Scene::OnUpdate(DeltaTime dt)
	{

		//updating the scripts
		m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
		{
			if (!nsc.Instance)
			{
				nsc.InstantiateFunction();
				nsc.Instance->m_Entity = Entity{ entity, this };
				nsc.OnCreateFunction(nsc.Instance);
			}

			nsc.OnUpdateFunction(nsc.Instance, dt);

		});

		//rendering the scene
		Camera* mainCamera{ nullptr };
		glm::mat4* cameraTransform{ nullptr };
		{
			auto view { m_Registry.view<TransformComponent, CameraComponent>() };
			for (auto entity : view)
			{
				auto [transform, camera] { view.get<TransformComponent, CameraComponent>(entity) };

				if (camera.Primary)
				{
					mainCamera = &camera.Camera;
					cameraTransform = &transform.Transform;
					break;
				}

			}
		}

		//rendering the scene
		if (mainCamera && cameraTransform)
		{
			{
				Renderer2D::BeginScene(*mainCamera, *cameraTransform);

				auto group{ m_Registry.group<TransformComponent, SpriteRendererComponent>() };
				for (auto entity : group)
				{
					auto [transform, spriteRenderer] { group.get<TransformComponent, SpriteRendererComponent>(entity) };

					Renderer2D::DrawQuad(transform, spriteRenderer.Color);
				}

				Renderer2D::EndScene();
			}
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

	//entt::registry::view<>() is faster for single components
	//entt::registry::group<>() is faster for multiple component
	
}