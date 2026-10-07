#pragma once

#include "Dark/Scene/Scene.h"

#include <ecs_entt.hpp>

namespace Dark
{
	
	class Entity
	{
	private:

		entt::entity m_Handle{0};

		Scene* m_SceneRef{ nullptr };

	public:
		Entity() = default;
		Entity(const Entity& other) = default;
		Entity(entt::entity handle, Scene* scene);

		template<typename... T>
		bool HasAllofComponent();

		template<typename... T>
		bool HasAnyofComponent();

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args);

		template<typename T>
		void RemoveComponent();

		template<typename... T>
		decltype(auto) GetComponents();

		template<typename... T>
		decltype(auto) TryGetComponents();

		inline entt::entity GetEntityHandle() { return m_Handle; }

	};

	template<typename... T>
	bool Entity::HasAllofComponent()
	{
		return m_SceneRef->m_Registry.all_of<T...>(m_Handle);
	}

	template<typename... T>
	bool Entity::HasAnyofComponent()
	{
		return m_SceneRef->m_Registry.any_of<T...>(m_Handle);
	}

	template<typename T, typename... Args>
	T& Entity::AddComponent(Args&&... args)
	{
		DARK_CORE_ASSERT(!(HasAllofComponent<T>() || HasAnyofComponent<T>()), "Entity Already Has the Component!");

		return m_SceneRef->m_Registry.emplace<T>(m_Handle, std::forward<Args>(args)...);
	}

	template<typename T>
	void Entity::RemoveComponent()
	{
		DARK_CORE_ASSERT((HasAllofComponent<T>() || HasAnyofComponent<T>()), "Entity Doesn't Have the Component!");

		m_SceneRef->m_Registry.remove<T>(m_Handle);
	}

	template<typename... T>
	decltype(auto) Entity::GetComponents()
	{
		DARK_CORE_ASSERT((HasAllofComponent<T...>() || HasAnyofComponent<T...>()), "Entity Doesn't Have the Component!");

		return m_SceneRef->m_Registry.get<T...>(m_Handle);
	}

	template<typename... T>
	decltype(auto) Entity::TryGetComponents()
	{
		DARK_CORE_ASSERT((HasAllofComponent<T...>() || HasAnyofComponent<T...>()), "Entity Doesn't Have the Component!");

		return m_SceneRef->m_Registry.try_get<T...>(m_Handle);
	}


}