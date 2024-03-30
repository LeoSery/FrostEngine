#include "Spawner.h"
#include "ECS/Component/Components/SpriteRenderer.h"

Spawner::Spawner(std::string _name, GameObject* _parent) : GameObject(_name, _parent){}

Spawner* Spawner::New(std::string _name, GameObject* _parent)
{
	Spawner* result = new Spawner(_name, _parent);
	result->Init();
#ifndef Release
	result->AddComponent<frost::ECS::SpriteRenderer>();
#endif // DEBUG


	return nullptr;
}

void Spawner::Start()
{
	// Start the GameObject
	m_SpawnTimer = 0.0f;
	m_SpawnRate = 1.0f;
	m_SpawnCount = 0;
	m_SpawnLimit = 10;

	GameObject::Start();
}

void Spawner::Tick(float _DeltaTime)
{
	_DeltaTime;
}
