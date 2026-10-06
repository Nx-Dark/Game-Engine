#pragma once

//ECS entt header------
#include "ecs_entt.hpp"
//---------------------

#include "Dark/Core/DeltaTime.h"

namespace Dark
{

	class DARK_API Scene
	{

	private:

		//container where Entity ID's and the Componenet data is stored!;
		entt::registry m_Registry{};

	public:
		Scene();
		~Scene();

		entt::entity CreateEntity();

		//TEMP SHIT
		inline entt::registry& GetReg() { return m_Registry; }

		void OnUpdate(DeltaTime dt);
	};

}