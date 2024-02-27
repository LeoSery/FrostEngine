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

	void Transform::Update(float /*_DeltaTime*/)
	{
		
	}

	void Transform::Destroy()
	{

	}

	void Transform::GetData(bool _ForceLoggerDraw) const
	{
		frost::utils::Logger* Logger = frost::utils::Logger::GetInstance();

		std::string PosString = std::format("{{ Position: [x: {:.2f} y: {:.2f}];", position.x, position.y);
		std::string RotString = std::format(" Rotation: {:.2f};", rotation);
		std::string ScaleString = std::format(" Scale: [x: {:.2f} y: {:.2f}]; }}", scale.x, scale.y);

		Logger->LogInfo(std::format("- Transform: {} {} {}", PosString, RotString, ScaleString));

		if (_ForceLoggerDraw)
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
