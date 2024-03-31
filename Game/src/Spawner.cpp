// Engine includes
#include "ECS/Component/Components/SpriteRenderer.h"

// Game includes
#include "Spawner.h"

#include <Utils/Logger.h>
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
	m_spawnTimer	=	0.0f;
	m_spawnRate		=	0.8f;
	m_spawnCount	=	0;
	m_spawnLimit	=	4;
	m_KillCount		=	0;
	m_KillLimit		=	45;

	// Start the GameObject
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

void Spawner::OnEnnemyDeath(frost::ECS::GameObject* Killed)
{

	// Remove the ennemy from the list
	auto it = std::find_if(m_SpawnedObjects.begin(), m_SpawnedObjects.end(), [Killed](frost::ECS::GameObject* obj) { return obj->GetUUID() == Killed->GetUUID(); });
	if (it == m_SpawnedObjects.end())
	{
		// The ennemy is not in the list
		frost::utils::Logger::GetInstance()->LogError("Ennemy not found in the list");
		return;
	}
	m_SpawnedObjects.erase(it);


	// Update the count
	m_spawnCount--;
	if (m_spawnCount < 0)
		m_spawnCount = 0;

	// Check if we need to spawn more ennemies or stop the game
	m_KillCount++;

	if (m_KillCount >= m_KillLimit)
	{
		m_KillCount = 0;
		m_spawnLimit = 0;
	}

}

void Spawner::Spawn(glm::vec2 _spawnLocation)
{
	_spawnLocation;
	m_spawnCount++;
	m_SpawnedObjects.push_back(Ennemi::New("Ennemi" + std::to_string(m_SpawnedObjects.size()), _spawnLocation, this->GetParent(), m_player, this));
}

float Spawner::GetRandomInRange(float min, float max)
{
	return  (max - min) * ((((float)rand()) / (float)RAND_MAX)) + min;
}
