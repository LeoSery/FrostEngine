#pragma once
#include "ECS/Entity/GameObject.h"

class MovementScript;

class Projectile :public frost::ECS::GameObject
{
public:
	static Projectile* New(std::string _name, GameObject* _parent);
	Projectile(std::string _name, GameObject* _parent);
	virtual void Start();
	virtual void Update(float _DeltaTime);

private:
	MovementScript* m_MovementScript;

};

