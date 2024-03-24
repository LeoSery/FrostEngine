#include <ECS/Component/Components/SpriteRenderer.h>

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
	this->AddComponent<frost::ECS::SpriteRenderer>()->SetTexture("PlayerShip/PlayerShip_FullHealh.png");
	m_MovementScript = this->AddComponent<MovementScript>();
}

void Projectile::Start()
{
	GameObject::Start();
	GetTransform().isMovingEntity = true;

}

void Projectile::Tick(float _DeltaTime)
{
	_DeltaTime;
	m_MovementScript->AddAcceleration(GetTransform().GetForwardVector());
}
