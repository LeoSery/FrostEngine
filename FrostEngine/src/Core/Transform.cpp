#include "Core/Transform.h"

#include <ostream>

namespace frost::core
{
	Transform::Transform(const glm::vec2& _Position, const float& _Rotation, const glm::vec2& _Scale)
	{
		position = _Position;
		rotation = _Rotation;
		scale = _Scale;
	}

	void Transform::GetData(std::ostream& _Stream) const
	{
		_Stream << "Position: " << position.x << " " << position.y << " " << std::endl;
		_Stream << "Rotation: " << rotation << " " << rotation << " " << rotation << std::endl;
		_Stream << "Scale: " << scale.x << " " << scale.y << " " << std::endl;
	}
}
