#include "ECS/Component/Components/Transform.h"

namespace frost::ECS
{
	Transform::Transform(GameObject& _GameObject) : IComponent(_GameObject)
	{
		
	}

	Transform::~Transform()
	{

	}

	void Transform::Start()
	{

	}

	void Transform::Update(float /*fDeltaTime*/)
	{
		
	}

	void Transform::Destroy()
	{

	}

	void Transform::GetData(std::ostream& _Stream) const
	{
		_Stream << "Position: " << position.x << " " << position.y << " " << std::endl;
		_Stream << "Rotation: " << rotation << std::endl;
		_Stream << "Scale: " << scale.x << " " << scale.y << " " << std::endl;
	}

	void Transform::Translate(const glm::vec2& _Translation)
	{
		position += _Translation;
	}

	void Transform::Rotate(float _Rotation)
	{
		rotation += _Rotation;
	}

	void Transform::Scale(const glm::vec2& _Scale)
	{
		scale *= _Scale;
	}
}
