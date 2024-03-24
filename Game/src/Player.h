#pragma once
#include "ECS/Entity/GameObject.h"

class MovementScript;

class Player : public frost::ECS::GameObject
{
public:
	static Player* New(std::string _name, GameObject* _parent);
	Player(std::string _name, GameObject* _parent);
	virtual void Start();

	virtual void Update(float _DeltaTime) override;

private:
	void MoveForward();
	void MoveBackward();
	void MoveLeft();
	void MoveRight();
	
	void Fire();

private:
	MovementScript* m_MovementScript;
};

