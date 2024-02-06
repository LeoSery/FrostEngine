#include "Core/Transform.h"

#include <ostream>

namespace frost::core
{
	Transform::Transform(const glm::vec3& _Position, const glm::vec3& _Rotation, const glm::vec3& _Scale)
	{
		position = _Position;
		rotation = _Rotation;
		scale = _Scale;
	}

	void Transform::GetData(std::ostream& _Stream) const
	{
		_Stream << "Position: " << position.x << " " << position.y << " " << position.z << std::endl;
		_Stream << "Rotation: " << rotation.x << " " << rotation.y << " " << rotation.z << std::endl;
		_Stream << "Scale: " << scale.x << " " << scale.y << " " << scale.z << std::endl;
	}
}
