#pragma once
#include "ECS/Component/IComponent.h"
#include <glm/glm.hpp>

class GameObject;

#define SMALLNUMBER 1.e-7f
#define SMALLVECTOR2 glm::vec2(1.e-7f, 1.e-7f)
#define ZeroVector2 glm::vec2(0.0f, 0.0f)

class MovementScript : public frost::ECS::IComponent
{
public:

	// Constructors and Destructors
	MovementScript(frost::ECS::GameObject& _GameObject);
	~MovementScript();

	// Frost engine life cycle methods
	void Start() override;
	void Update(float _DeltaTime) override;

	void AddAcceleration(glm::vec2 _Acceleration);
	void AddRotationAcceleration(float _Acceleration);


#pragma region Movement

public : //Movement Variables
	float m_friction = 2.0f;
	float m_MaxSpeed = 20.0f;
	glm::vec2 m_CurrentVelocity = { 0.0f  , 0.0f };
	glm::vec2 m_InputAcceleration = { 0.0f  , 0.0f };

	bool alwaysApplyFriction = false;

#pragma endregion

#pragma region Rotation
public:
	float m_Rotationfriction = 5.0f;
	float m_MaxRotationSpeed = 20.f;
	float m_CurrentRotationVelocity = 0.0f;
	float m_InputRotationAcceleration = 0.0f;
#pragma endregion

private: 
	frost::ECS::GameObject* m_OwningObject;
};

