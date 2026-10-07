#pragma once

//ECS Entity------
#include <ecs_entt.hpp>
//---------------------

#include "Dark/Core/DeltaTime.h"

namespace Dark
{

	class Entity;

	class DARK_API Scene
	{

	private:

		//container where Entity ID's and the Componenet data is stored!;
		entt::registry m_Registry{};

		//setting entity as the friend class so it can access Scene's member variables;
		friend class Entity;

	public:
		Scene();
		~Scene();

		void OnUpdate(DeltaTime dt);

		//creating entity in the current active scene;
		Entity CreateEntity(const std::string& name = std::string{});

	};

}