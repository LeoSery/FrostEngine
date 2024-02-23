#include "ECS/Component/Components/Transform.h"
#include "Utils/Logger.h"

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

	void Transform::GetData(bool _ShowImmediately) const
	{
		frost::utils::Logger* Logger = frost::utils::Logger::GetInstance();

		std::string PosString = "{ Position: [x: " + std::to_string(position.x) + " y: " + std::to_string(position.y) + "];";
		std::string RotString = " Rotation: " + std::to_string(rotation) + ";";
		std::string ScaleString = " Scale: [x: " + std::to_string(scale.x) + " y: " + std::to_string(scale.y) + "]; }";

		Logger->LogInfo("- Transform: " + PosString + RotString + ScaleString);

		if (_ShowImmediately)
			Logger->Show();
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
