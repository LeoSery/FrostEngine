#include "Ennemi.h"
#include "ECS/Component/Components/BoxCollider.h"
#include "ECS/Component/Components/SpriteRenderer.h"
#include <iostream>

Ennemi* Ennemi::New(std::string _name, GameObject* _parent)
{
	Ennemi* result = new Ennemi(_name, _parent);
	result->Init();
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
	m_SpriteRenderer = this->AddComponent<frost::ECS::SpriteRenderer>();
	m_SpriteRenderer->SetTexture("PlayerShip/PlayerShip_FullHealh.png");
	m_BoxCollider = this->AddComponent<frost::ECS::BoxCollider>();
	m_BoxCollider->m_collisionChannel = frost::ECS::CollisionChannel::Ennemy;
	m_BoxCollider->m_collisionSettings.emplace(std::pair<frost::ECS::CollisionChannel, frost::ECS::CollisionResponse>(frost::ECS::Projectile, frost::ECS::Block));
	m_BoxCollider->m_collisionSettings.emplace(std::pair<frost::ECS::CollisionChannel, frost::ECS::CollisionResponse>(frost::ECS::Player, frost::ECS::Block));
	m_BoxCollider->m_collisionSettings.emplace(std::pair<frost::ECS::CollisionChannel, frost::ECS::CollisionResponse>(frost::ECS::Ennemy, frost::ECS::Block));

}

void Ennemi::Tick(float _DeltaTime)
{
	_DeltaTime;
}

void Ennemi::OnCollisionEnter(const frost::ECS::S_CollisionData* _CollisionData)
{
	_CollisionData;
}
