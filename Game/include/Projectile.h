#pragma once
#include "ECS/Entity/GameObject.h"

class MovementScript;
class BoxCollider;
class Projectile :public frost::ECS::GameObject
{
public:
	static Projectile* New(std::string _name, GameObject* _parent);
	Projectile(std::string _name, GameObject* _parent);
	virtual void Start();
	virtual void Tick(float _DeltaTime);
	virtual void OnCollisionEnter(const frost::ECS::S_CollisionData* _CollisionData) override;
private:
	MovementScript* m_MovementScript;
	frost::ECS::BoxCollider* m_BoxCollider;
};

