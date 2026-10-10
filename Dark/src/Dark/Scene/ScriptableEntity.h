#pragma once

#include "Dark/Scene/Entity.h"

namespace Dark
{

	class ScriptableEntity
	{

	private:

		Entity m_Entity{};

		friend class Scene;

	public:

		template<typename... T>
		inline bool HasAllofComponent()
		{
			return m_Entity.HasAllofComponent<T...>();
		}

		template<typename... T>
		inline bool HasAnyofComponent()
		{
			return m_Entity.HasAnyofComponent<T...>();
		}

		template<typename T, typename... Args>
		inline T& AddComponent(Args&&... args)
		{
			return m_Entity.AddComponent<T>(std::forward<Args>(args)...);
		}

		template<typename T>
		inline void RemoveComponent()
		{
			m_Entity.RemoveComponent<T>();
		}

		template<typename... T>
		inline decltype(auto) GetComponents()
		{
			return m_Entity.GetComponents<T...>();
		}

		template<typename... T>
		inline decltype(auto) TryGetComponents()
		{
			return m_Entity.TryGetComponents<T...>();
		}

	};

}