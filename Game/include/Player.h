#pragma once
#include "ECS/Entity/GameObject.h"
#include "ECS/Component/Components/BoxCollider.h"
#include "ECS/Component/Components/SpriteRenderer.h"

namespace frost::ECS
{
	struct S_CollisionData;
}

class MovementScript;
class BoxCollider;
class SpriteRenderer;

class Player : public frost::ECS::GameObject
{
public:
	static Player* New(std::string _name, GameObject* _parent);
	Player(std::string _name, GameObject* _parent);

	virtual void Start();
	virtual void Tick(float _DeltaTime) override;
	virtual void OnCollisionEnter(const frost::ECS::S_CollisionData* _CollisionData) override;
	virtual void TakeDamage(unsigned int _Damage) override;


private: //Methods
	void MoveForward();
	void MoveBackward();
	void MoveLeft();
	void MoveRight();
	void Fire();



private: //Attributes
	unsigned int m_Health = 100;
	unsigned int m_MaxHealth = 100;
	MovementScript* m_MovementScript;
	frost::ECS::BoxCollider* m_BoxCollider;
	frost::ECS::SpriteRenderer* m_SpriteRenderer;
 
};

