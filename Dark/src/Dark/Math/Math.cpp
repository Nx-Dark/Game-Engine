#include "dpch.h"
#include "Math.h"

namespace Dark::Math {

	bool DecomposeTransfrom(const glm::mat4& transform, glm::vec3& translation, glm::vec3& oreintation, glm::vec3& scale)
	{
		//translation
		translation = glm::vec3{ transform[3] };

		//scale
		scale.x = glm::length(glm::vec3(transform[0]));
		scale.y = glm::length(glm::vec3(transform[1]));
		scale.z = glm::length(glm::vec3(transform[2]));

		//rotation
		glm::mat3 rotMat{
			glm::vec3(transform[0]) / scale.x,
			glm::vec3(transform[1]) / scale.y,
			glm::vec3(transform[2]) / scale.z,
		};

		oreintation = glm::eulerAngles(glm::quat{ rotMat });

		return true;
	}

}