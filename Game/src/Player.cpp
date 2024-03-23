// Engine includes
#include "Core/Input/Input.h"

// Game includes
#include "Player.h"
#include "MovementScript.h"

#include "ECS/Entity/GameObject.h"
#include "MovementScript.h"
Player::Player(std::string _name, GameObject* _Parent) : GameObject(_name, _Parent)
{

	m_MovementScript = AddComponent<MovementScript>();

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

	//// Create Inputs
	// Forward
	frost::core::Input::GetInstance()->AddAction("MovingForward");
	frost::core::Input::GetInstance()->AddActionToKey(frost::core::Input::Key::W, "MovingForward");
	frost::core::Input::GetInstance()->BindFunctionToAction("MovingForward", this, [this]() { MoveForward(); }, frost::core::Input::ActionType::OnGoing);

	// Backward
	frost::core::Input::GetInstance()->AddAction("MovingBackward");
	frost::core::Input::GetInstance()->AddActionToKey(frost::core::Input::Key::S, "MovingBackward");
	frost::core::Input::GetInstance()->BindFunctionToAction("MovingBackward", this, [this]() { MoveBackward(); }, frost::core::Input::ActionType::OnGoing);

	// Left
	frost::core::Input::GetInstance()->AddAction("MovingLeft");
	frost::core::Input::GetInstance()->AddActionToKey(frost::core::Input::Key::A, "MovingLeft");
	frost::core::Input::GetInstance()->BindFunctionToAction("MovingLeft", this, [this]() { MoveLeft(); }, frost::core::Input::ActionType::OnGoing);

	// Forward
	frost::core::Input::GetInstance()->AddAction("MovingRight");
	frost::core::Input::GetInstance()->AddActionToKey(frost::core::Input::Key::D, "MovingRight");
	frost::core::Input::GetInstance()->BindFunctionToAction("MovingRight", this, [this]() { MoveRight(); }, frost::core::Input::ActionType::OnGoing);
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

	m_MovementScript->AddAcceleration(GetTransform().GetForwardVector() * -1.0f );
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
