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
	static Ennemi* New(std::string _name, glm::vec2 _location ,GameObject* _parent , GameObject* _objectToFocus);
	Ennemi(std::string _name, GameObject* _parent);
	~Ennemi();

	virtual void Start();
	virtual void Tick(float _DeltaTime) override;
	virtual void OnCollisionEnter(const frost::ECS::S_CollisionData* _CollisionData) override;

private:
	frost::ECS::SpriteRenderer* m_spriteRenderer;
	frost::ECS::BoxCollider*	m_boxCollider;

	MovementScript* m_movementScript;
	GameObject* m_objectToFocus;
};

