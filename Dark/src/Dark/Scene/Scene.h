#pragma once

#include "ecs_entt.hpp"

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
	};

}