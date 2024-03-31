#include <ECS/Component/Components/SpriteRenderer.h>
#include <ECS/Component/Components/BoxCollider.h>

#include "Ennemi.h"
#include "Projectile.h"
#include "MovementScript.h"

Projectile* Projectile::New(std::string _name, GameObject* _parent , glm::vec2 _baseVelocity)
{
	Projectile* result = new Projectile(_name, _parent);
	result->Init();
	result->GetTransform().Scale(glm::vec2(0.8f, 0.8f));
	result->m_MovementScript->m_MaxSpeed = 80;
	result->m_MovementScript->m_friction = 1.0f;
	result->m_MovementScript->m_CurrentVelocity = _baseVelocity * 0.8f;
	result->m_MovementScript->alwaysApplyFriction = true;
	return result;
}

Projectile::Projectile(std::string _name, GameObject* _parent)
	: GameObject(_name, _parent)
{
}

void Projectile::Start()
{
	GameObject::Start();
	GetTransform().isMovingEntity = true;
	this->AddComponent<frost::ECS::SpriteRenderer>()->SetTexture("PlayerShip/Projectile.png");
	m_MovementScript = this->AddComponent<MovementScript>();
	m_BoxCollider = this->AddComponent<frost::ECS::BoxCollider>();
	m_BoxCollider->m_collisionChannel = frost::ECS::E_CollisionChannel::Projectile;
	m_BoxCollider->m_collisionSettings.emplace(std::pair<frost::ECS::E_CollisionChannel, frost::ECS::E_CollisionResponse>(frost::ECS::Ennemy, frost::ECS::Block));
}

void Projectile::Tick(float _DeltaTime)
{
	_DeltaTime;
	m_MovementScript->AddAcceleration(GetTransform().GetForwardVector());

	LifeTime -= _DeltaTime;
	if (LifeTime <= 0)
	{
		Destroy();
	}
}

void Projectile::OnCollisionEnter(const frost::ECS::S_CollisionData* _CollisionData)
{
	_CollisionData;
	if (_CollisionData->otherCollider->GetParentObject().HasTag("Ennemi") && !_CollisionData->otherCollider->GetParentObject().IsDirty())
	{
		_CollisionData->otherCollider->GetParentObject().Destroy();
		Destroy();
	}
}
