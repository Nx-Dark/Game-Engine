#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

//custom functions for glm math library
namespace Dark::Math
{
	bool DecomposeTransfrom(const glm::mat4& transform, glm::vec3& translation, glm::vec3& oreintation, glm::vec3& scale);
}