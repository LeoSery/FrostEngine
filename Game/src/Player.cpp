// Engine includes
#include "Core/Input/Input.h"
#include "ECS/Entity/GameObject.h"
#include "ECS/Component/Components/SpriteRenderer.h"
#include "ECS/Component/Components/BoxCollider.h"
#include "Utils/Logger.h"

// Game includes
#include "Player.h"
#include "Projectile.h"
#include "MovementScript.h"
#include <iostream>


Player::Player(std::string _name, GameObject* _Parent) : GameObject(_name, _Parent)
{
	m_MovementScript = AddComponent<MovementScript>();
	this->AddComponent<frost::ECS::SpriteRenderer>()->SetTexture("PlayerShip/PlayerShip_FullHealh.png");
}

Player* Player::New(std::string _name, GameObject* _parent)
{
	Player* result = new Player(_name, _parent);
	result->Init();
	return result;
}

void Player::Start()
{
	// Start the GameObject
	GameObject::Start();

	GetTransform().isMovingEntity = true;

#pragma region "Input"
	// Forward
	frost::core::Input::GetInstance()->AddAction("MovingForward");
	frost::core::Input::GetInstance()->AddActionToKey(frost::core::Input::E_Key::W, "MovingForward");
	frost::core::Input::GetInstance()->BindFunctionToAction("MovingForward", this, [this]() { MoveForward(); }, frost::core::Input::E_ActionType::OnGoing);

	// Backward
	frost::core::Input::GetInstance()->AddAction("MovingBackward");
	frost::core::Input::GetInstance()->AddActionToKey(frost::core::Input::E_Key::S, "MovingBackward");
	frost::core::Input::GetInstance()->BindFunctionToAction("MovingBackward", this, [this]() { MoveBackward(); }, frost::core::Input::E_ActionType::OnGoing);

	// Left
	frost::core::Input::GetInstance()->AddAction("MovingLeft");
	frost::core::Input::GetInstance()->AddActionToKey(frost::core::Input::E_Key::A, "MovingLeft");
	frost::core::Input::GetInstance()->BindFunctionToAction("MovingLeft", this, [this]() { MoveLeft(); }, frost::core::Input::E_ActionType::OnGoing);

	// Forward
	frost::core::Input::GetInstance()->AddAction("MovingRight");
	frost::core::Input::GetInstance()->AddActionToKey(frost::core::Input::E_Key::D, "MovingRight");
	frost::core::Input::GetInstance()->BindFunctionToAction("MovingRight", this, [this]() { MoveRight(); }, frost::core::Input::E_ActionType::OnGoing);

	// Fire
	frost::core::Input::GetInstance()->AddAction("Fire");
	frost::core::Input::GetInstance()->AddActionToKey(frost::core::Input::E_Key::SPACE, "Fire");
	frost::core::Input::GetInstance()->BindFunctionToAction("Fire", this, [this]() { Fire(); }, frost::core::Input::E_ActionType::Press);
}

void Player::Tick(float _DeltaTime)
{
	_DeltaTime;
	//std::cout << "Player Update" << std::endl;
}

void Player::OnCollisionEnter(const frost::ECS::S_CollisionData* _CollisionData)
{
	std::string ColName = _CollisionData->otherCollider->GetParentObject().GetName();
	frost::utils::Logger::LogInfo("Collision with " + ColName);
}

void Player::MoveForward()
{
	//frost::utils::Logger::LogInfo("Moving forward");
	//GetTransform().position.y += 0.01f;
	m_MovementScript->AddAcceleration(GetTransform().GetForwardVector());
}

void Player::MoveBackward()
{
	//frost::utils::Logger::LogInfo("Moving backward");
	//GetTransform().position.y -= 0.01f;
	m_MovementScript->AddAcceleration(GetTransform().GetForwardVector() * -1.0f);
}

void Player::MoveLeft()
{
	//frost::utils::Logger::LogInfo("Moving Left");
	//GetTransform().position.x -= 0.01f;

	//m_MovementScript->AddAcceleration({ -1.0f,0.0f });
	m_MovementScript->AddRotationAcceleration(-1.0f);
}

void Player::MoveRight()
{
	//frost::utils::Logger::LogInfo("Moving Right");
	//GetTransform().position.x += 0.01f;

	m_MovementScript->AddRotationAcceleration(1.0f);
}

void Player::Fire()
{
	//frost::utils::Logger::LogInfo("Fire");
	GameObject* projectile = Projectile::New("Projectile", this);
	projectile->GetTransform().position = GetTransform().position;
	projectile->GetTransform().rotation = GetTransform().rotation;
}
