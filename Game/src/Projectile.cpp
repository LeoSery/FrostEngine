#include <ECS/Component/Components/SpriteRenderer.h>
#include <ECS/Component/Components/BoxCollider.h>

#include "Ennemi.h"
#include "Projectile.h"
#include "MovementScript.h"

Projectile* Projectile::New(std::string _name, GameObject* _parent)
{
	Projectile* result = new Projectile(_name, _parent);
	result->Init();
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
	this->AddComponent<frost::ECS::SpriteRenderer>()->SetTexture("PlayerShip/PlayerShip_FullHealh.png");
	m_MovementScript = this->AddComponent<MovementScript>();
	m_BoxCollider = this->AddComponent<frost::ECS::BoxCollider>();
	m_BoxCollider->m_collisionChannel = frost::ECS::CollisionChannel::Projectile;
	m_BoxCollider->m_collisionSettings.emplace(std::pair<frost::ECS::CollisionChannel, frost::ECS::CollisionResponse>(frost::ECS::Ennemy, frost::ECS::Block));
}

void Projectile::Tick(float _DeltaTime)
{
	_DeltaTime;
	m_MovementScript->AddAcceleration(GetTransform().GetForwardVector());
}

void Projectile::OnCollisionEnter(const frost::ECS::S_CollisionData* _CollisionData)
{
	_CollisionData;
	if (dynamic_cast<Ennemi*>(&_CollisionData->otherCollider->GetParentObject()) != nullptr)
	{
		Ennemi* ColName = &dynamic_cast<Ennemi&>(_CollisionData->otherCollider->GetParentObject());
		ColName->Destroy();
		Destroy();
	}
}
