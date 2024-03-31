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
class Spawner;

class Ennemi : public frost::ECS::GameObject
{
public:
	//Create ennemi
	static Ennemi* New(std::string _name, GameObject* _parent);
	//Create ennemi with a location and a spawner 
	static Ennemi* New(std::string _name, glm::vec2 _location ,GameObject* _parent , GameObject* _objectToFocus , Spawner* _spawner);
	Ennemi(std::string _name, GameObject* _parent);
	~Ennemi();

	virtual void Start();
	virtual void Tick(float _DeltaTime) override;
	virtual void OnCollisionEnter(const frost::ECS::S_CollisionData* _CollisionData) override;

private:
	//call spawner to tell it we are dead
	void OnDestroy() override;

private:
	frost::ECS::SpriteRenderer* m_spriteRenderer;
	frost::ECS::BoxCollider*	m_boxCollider;

	MovementScript* m_movementScript;
	GameObject* m_objectToFocus;
	Spawner* m_spawner;
};

