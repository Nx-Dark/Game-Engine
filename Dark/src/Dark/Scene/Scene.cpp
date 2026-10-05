#include "dpch.h"
#include "Scene.h"

#include <glm/glm.hpp>

namespace Dark
{
	static void DoMath(const glm::mat4& transform)
	{

	}

	static void onConstruct(entt::registry&, entt::entity entity)
	{

	}

	Scene::Scene()
	{

		//Practicing EnTT ECS
		struct MeshComponent {};
		struct TransformComponent
		{
			glm::mat4 Transform{ 1.0f };

			TransformComponent() = default;
			TransformComponent(const TransformComponent&) = default;
			TransformComponent(const glm::mat4& transform)
				: Transform{transform} {}

			inline operator const glm::mat4&() { return Transform; }
		};

		TransformComponent transformComp{ glm::mat4{1.0f} };
		DoMath(transformComp);

		entt::entity entity{ m_Registry.create() };

		m_Registry.on_construct<TransformComponent>().connect<&onConstruct>();
		m_Registry.emplace<TransformComponent>(entity, glm::mat4{ 1.0f });

		if (auto* component = m_Registry.try_get<TransformComponent>(entity)) {
			DARK_CORE_INFO("SUP");
		}

		auto view{ m_Registry.view<TransformComponent>() };
		for (auto entity : view)
		{
			TransformComponent& transform{ m_Registry.get<TransformComponent>(entity) };
			transform.Transform = glm::mat4{ 1.0f };
		}

		auto group{ m_Registry.group<TransformComponent, MeshComponent>() };
		for (auto entity : group)
		{
			auto& [transform, mesh] { m_Registry.get<TransformComponent, MeshComponent>(entity) };
			transform.Transform = glm::mat4{ 1.0f };
		}
	}

	Scene::~Scene()
	{

	}

}