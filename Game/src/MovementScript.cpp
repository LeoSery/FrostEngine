#include "MovementScript.h"
#include "ECS/Entity/GameObject.h"
#include "ECS/Component/Components/Transform.h"
#include <Utils/Logger.h>
#include <iostream>

MovementScript::MovementScript(frost::ECS::GameObject& _GameObject) 
	: frost::ECS::IComponent(_GameObject)
{
	Start();
}

MovementScript::~MovementScript()
{
}

void MovementScript::Start()
{
	m_OwningObject = &GetParentObject();
}

void MovementScript::Update(float _DeltaTime)
{
	_DeltaTime;


	//Update Rotation
	float futureRotationVelocity = m_CurrentRotationVelocity + (m_InputRotationAcceleration * m_MaxRotationSpeed) - (m_Rotationfriction * m_CurrentRotationVelocity);
	m_InputRotationAcceleration = 0.0f; //Consume the acceleration

	if (glm::abs(m_CurrentRotationVelocity) > m_MaxRotationSpeed)
	{
		m_CurrentRotationVelocity = m_CurrentRotationVelocity * (m_MaxRotationSpeed / glm::abs(m_CurrentRotationVelocity));
	}
	m_CurrentRotationVelocity += futureRotationVelocity * _DeltaTime;

	m_OwningObject->GetTransform().rotation += m_CurrentRotationVelocity;



	//Update the position
	glm::vec2 futureVelocity = m_CurrentVelocity + (m_InputAcceleration * m_MaxSpeed)  - (m_friction * m_CurrentVelocity);
	glm::vec2 Delta = glm::length(futureVelocity)> SMALLNUMBER ? futureVelocity : ZeroVector2;
	m_InputAcceleration = { 0.0f, 0.0f }; //Consume the acceleration
	m_CurrentVelocity += Delta * _DeltaTime;
	ClampVelocity();
	m_OwningObject->GetTransform().position += m_CurrentVelocity;


}

void MovementScript::Destroy()
{
}

void MovementScript::AddAcceleration(glm::vec2 _Acceleration)
{
		m_InputAcceleration += _Acceleration;
}

void MovementScript::ClampVelocity()
{
	if (glm::length(m_CurrentVelocity) > m_MaxSpeed)
	{
		m_CurrentVelocity =  (m_MaxSpeed / glm::length(m_CurrentVelocity)) * m_CurrentVelocity;
	}

}

void MovementScript::AddRotationAcceleration(float _Acceleration)
{


	m_InputRotationAcceleration = _Acceleration;

}

