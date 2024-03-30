#pragma once

#include "ECS/Entity/GameObject.h"

class MovementScript;

namespace frost::ECS
{
	struct S_CollisionData;
}

class Player : public frost::ECS::GameObject
{
public:
	static Player* New(std::string _name, GameObject* _parent);
	Player(std::string _name, GameObject* _parent);
	virtual void Start();

	virtual void Tick(float _DeltaTime) override;
	virtual void OnCollisionEnter(const frost::ECS::S_CollisionData* _CollisionData) override;

private:
	void MoveForward();
	void MoveBackward();
	void MoveLeft();
	void MoveRight();

	void Fire();

private:
	MovementScript* m_MovementScript;
};

