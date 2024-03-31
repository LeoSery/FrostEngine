#include "Ennemi.h"
#include "ECS/Component/Components/BoxCollider.h"
#include "ECS/Component/Components/SpriteRenderer.h"
#include "MovementScript.h"
#include "Spawner.h"
#include <iostream>

Ennemi* Ennemi::New(std::string _name, GameObject* _parent)
{
	Ennemi* result = new Ennemi(_name, _parent);
	result->Init();
	return result;
}

Ennemi* Ennemi::New(std::string _name, glm::vec2 _location, GameObject* _parent , GameObject* _objectToFocus, Spawner* _spawner)
{
	Ennemi* result = new Ennemi(_name, _parent);
	result->Init(_location, 0.0f, {1.0f,1.0f});
	result->GetTransform().isMovingEntity = true;
	result->m_objectToFocus = _objectToFocus;
	result->m_spawner = _spawner;
	return result;
}

Ennemi::Ennemi(std::string _name, GameObject* _parent) 
	: GameObject(_name, _parent)
{
	_parent;
	_name;
}

Ennemi::~Ennemi()
{

}

void Ennemi::Start()
{
	m_movementScript = AddComponent<MovementScript>();
	m_boxCollider = AddComponent<frost::ECS::BoxCollider>();
	m_spriteRenderer = AddComponent<frost::ECS::SpriteRenderer>();
	m_spriteRenderer->SetTexture("PlayerShip/EnnemiShip_Verydamaged.png");
	m_boxCollider->m_collisionChannel = frost::ECS::E_CollisionChannel::Ennemy;
	m_boxCollider->m_collisionSettings.emplace(std::pair<frost::ECS::E_CollisionChannel, frost::ECS::E_CollisionResponse>(frost::ECS::Projectile,frost::ECS::Block));
	m_boxCollider->m_collisionSettings.emplace(std::pair<frost::ECS::E_CollisionChannel, frost::ECS::E_CollisionResponse>(frost::ECS::Player	,frost::ECS::Block));
	m_boxCollider->m_collisionSettings.emplace(std::pair<frost::ECS::E_CollisionChannel, frost::ECS::E_CollisionResponse>(frost::ECS::Ennemy	,frost::ECS::Ignore));
	m_movementScript->m_MaxSpeed = 5;
	m_movementScript->m_Rotationfriction = 10;

	GameObject::Start();
}

void Ennemi::Tick(float _DeltaTime)
{
	_DeltaTime;
	
	if (!m_objectToFocus->IsDirty())
	{
		//Find Rotation

		glm::vec2 start = m_objectToFocus->GetTransform().position;
		glm::vec2 end = GetTransform().position;
		glm::vec2 direction = start - end;
		direction = glm::normalize(direction);
		float angle = atan2(direction.x, direction.y);
		GetTransform().rotation = angle;

		//Move
		m_movementScript->AddAcceleration(this->GetTransform().GetForwardVector());
	}
}

void Ennemi::OnCollisionEnter(const frost::ECS::S_CollisionData* _CollisionData)
{
	_CollisionData;
	if (! _CollisionData->otherCollider->GetParentObject().IsDirty())
	{
		_CollisionData->otherCollider->GetParentObject().TakeDamage(10);
		this->Destroy();
	};
}

void Ennemi::Destroy()
{
	m_spawner->OnEnnemyDeath(this);
	GameObject::Destroy();
}
