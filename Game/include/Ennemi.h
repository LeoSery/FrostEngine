#pragma once
#include "ECS/Entity/GameObject.h"

namespace frost
{
	namespace ECS
	{
		class SpriteRenderer;
		class BoxCollider;
	}
}
class MovementScript;

class Ennemi : public frost::ECS::GameObject
{
public:
	static Ennemi* New(std::string _name, GameObject* _parent);
	Ennemi(std::string _name, GameObject* _parent);
	~Ennemi();

	virtual void Start();
	virtual void Tick(float _DeltaTime) override;
	virtual void OnCollisionEnter(const frost::ECS::S_CollisionData* _CollisionData) override;

private:
	frost::ECS::SpriteRenderer* m_SpriteRenderer;
	frost::ECS::BoxCollider* m_BoxCollider;

	MovementScript* m_MovementScript;
};

