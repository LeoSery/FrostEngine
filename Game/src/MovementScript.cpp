#include "MovementScript.h"
#include "ECS/Entity/GameObject.h"
#include "ECS/Component/Components/Transform.h"
#include <Utils/Logger.h>
#include <iostream>

MovementScript::MovementScript(frost::ECS::GameObject& _GameObject) : frost::ECS::IComponent(_GameObject)
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
	//Update Rotation
	float Rotfriction = alwaysApplyFriction ? m_Rotationfriction : (m_Rotationfriction * ((glm::abs(m_InputRotationAcceleration) * -1) + 1));

	float RotationDelta =(m_InputRotationAcceleration * m_MaxRotationSpeed) - (m_CurrentRotationVelocity * Rotfriction);
	m_InputRotationAcceleration = 0.0f; //Consume the acceleration

	m_CurrentRotationVelocity += RotationDelta * _DeltaTime;
	if (m_CurrentRotationVelocity > m_MaxRotationSpeed)
	{
		m_CurrentRotationVelocity = m_MaxRotationSpeed;
	}
	m_OwningObject->GetTransform().rotation += m_CurrentRotationVelocity * _DeltaTime;



	//Update the position
	float Velfriction = alwaysApplyFriction ? m_friction : (m_friction * ((glm::length(m_InputAcceleration) * -1) + 1));
	glm::vec2 Delta = (m_InputAcceleration * m_MaxSpeed) - (Velfriction * m_CurrentVelocity);
	m_InputAcceleration = { 0.0f, 0.0f }; //Consume the acceleration

	m_CurrentVelocity += Delta * _DeltaTime ;
	m_CurrentVelocity = glm::length(m_CurrentVelocity) <= SMALLNUMBER ?  ZeroVector2 : m_CurrentVelocity;

	if (glm::length(m_CurrentVelocity) > m_MaxSpeed)
	{
		m_CurrentVelocity = (m_MaxSpeed / glm::length(m_CurrentVelocity)) * m_CurrentVelocity;
	}

	m_OwningObject->GetTransform().position += m_CurrentVelocity * _DeltaTime;
}

void MovementScript::AddAcceleration(glm::vec2 _Acceleration)
{
	m_InputAcceleration += _Acceleration;
}

void MovementScript::AddRotationAcceleration(float _Acceleration)
{
	m_InputRotationAcceleration = _Acceleration;
}

