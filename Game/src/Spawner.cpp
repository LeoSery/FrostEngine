#include "Spawner.h"
#include "ECS/Component/Components/SpriteRenderer.h"
#include <Ennemi.h>
#include <random>

Spawner::Spawner(std::string _name, GameObject* _parent) : GameObject(_name, _parent){}

Spawner* Spawner::New(std::string _name , glm::vec2 _position , GameObject* _parent , GameObject* _player)
{
	Spawner* result = new Spawner(_name, _parent);
	result->Init(_position, 0, result->m_size);
	result->m_player = _player;
#ifndef Release
	//result->AddComponent<frost::ECS::SpriteRenderer>();
#endif // DEBUG


	return nullptr;
}

void Spawner::Start()
{
	// Start the GameObject
	m_spawnTimer = 0.0f;
	m_spawnRate = 0.01f;
	m_spawnCount = 0;
	m_spawnLimit = 10;

	GameObject::Start();
}

void Spawner::Tick(float _DeltaTime)
{
	_DeltaTime;
	if (m_spawnCount < m_spawnLimit)
	{
		m_spawnTimer += _DeltaTime;
		if (m_spawnTimer >= m_spawnRate)
		{
			m_spawnTimer = 0.0f;
			glm::vec2 spawnLocation = glm::vec2(GetRandomInRange(-m_size.x, m_size.x), GetRandomInRange(-m_size.y, m_size.y)) + GetTransform().position;
			Spawn(spawnLocation);
		}
	}
}

void Spawner::Spawn(glm::vec2 _spawnLocation)
{
	_spawnLocation;
	Ennemi::New("Ennemi", _spawnLocation ,this->GetParent() , m_player);
	m_spawnCount++;
}

float Spawner::GetRandomInRange(float min, float max)
{
	return  (max - min) * ((((float)rand()) / (float)RAND_MAX)) + min;
}
