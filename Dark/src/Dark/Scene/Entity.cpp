#include <dpch.h>
#include "Entity.h"

namespace Dark
{

	Entity::Entity(entt::entity handle, Scene* scene)
		: m_Handle{ handle }, m_SceneRef { scene }
	{

	}

}