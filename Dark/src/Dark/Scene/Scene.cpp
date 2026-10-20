#include "dpch.h"
#include "Scene.h"
#include "Entity.h"

#include <glm/glm.hpp>
#include <glm/gtx/matrix_query.hpp>

#include "Dark/Scene/Components.h"

#include "Dark/Renderer/Renderer2D.h"

namespace Dark
{

	Scene::Scene()
	{	
		
	}

	Scene::~Scene()
	{
		m_Registry.clear();
	}

	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		m_ViewportWidth = width;
		m_ViewportHeight = height;

		//setting the projection/resizing the viewport of the non fixed aspect ratio camera components
		m_Registry.view<CameraComponent>().each([&](const auto entity, auto& camComp) 
		{

			if (!camComp.FixedAspectRatio)
				camComp.Camera.SetViewportSize(width, height);

		});
	}

	void Scene::OnUpdate(DeltaTime dt)
	{

		//updating the scripts
		m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
		{
			//TODO: Move the instantiation of the scripts to OnSceneCreate during runtime, rn we dont have a runtime
			if (!nsc.Instance)
			{
				nsc.Instance = nsc.InstantiateScript();
				nsc.Instance->m_Entity = Entity{ entity, this };
				nsc.Instance->OnCreate();
			}

			nsc.Instance->OnUpdate(dt);

		});

		//Retreving the camera and the camera transform
		Camera* mainCamera{ nullptr };
		glm::mat4 cameraTransform{ 1.0f };
		auto view{ m_Registry.view<TransformComponent, CameraComponent>() };
		for (const auto entity : view)
		{
			auto [transform, camera] { m_Registry.get<TransformComponent, CameraComponent>(entity) };

			if (camera.Primary)
			{
				mainCamera = &camera.Camera;
				cameraTransform = transform.GetTransform();
				break;
			}

		}

		//rendering the scene
		if (mainCamera)
		{
			Renderer2D::BeginScene(*mainCamera, cameraTransform);

			m_Registry.group<TransformComponent, SpriteRendererComponent>().each([](const auto entity, auto& tc, auto& src) 
			{
					
				Renderer2D::DrawQuad(tc.GetTransform(), src.Color);

			});

			Renderer2D::EndScene();
		}
	}
	
	//Creating the Entity
	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity e{ m_Registry.create(), this };
		e.AddComponent<TransformComponent>();
		TagComponent& tag{ e.AddComponent<TagComponent>() };
		tag.Tag = name.empty() ? "Entity" : name;
		return e;
	}

	void Scene::DestroyEntity(Entity entity)
	{
		m_Registry.destroy(entity);
	}


	template<typename T>
	void Scene::OnComponentAdded(Entity entity, T& component)
	{
		static_assert(false);
	}

	template<>
	void Scene::OnComponentAdded<TagComponent>(Entity entity, TagComponent& component)
	{

	}

	template<>
	void Scene::OnComponentAdded<TransformComponent>(Entity entity, TransformComponent& component)
	{

	}

	template<>
	void Scene::OnComponentAdded<SpriteRendererComponent>(Entity entity, SpriteRendererComponent& component)
	{

	}

	//whenever camera component gets created in the entt registry, this function gets called
	template<>
	void Scene::OnComponentAdded<CameraComponent>(Entity entity, CameraComponent& component)
	{
		component.Camera.SetViewportSize(m_ViewportWidth, m_ViewportHeight);
	}

	template<>
	void Scene::OnComponentAdded<NativeScriptComponent>(Entity entity, NativeScriptComponent& component)
	{

	}

	//entt::registry::view<>() is faster for single components
	//entt::registry::group<>() is faster for multiple component
	
}