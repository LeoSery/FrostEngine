#pragma once
#include "ECS/Entity/GameObject.h"

class Spawner : public frost::ECS::GameObject
{
public:
	static Spawner* New(std::string _name, glm::vec2 _position,GameObject* _parent , GameObject* _player);
	Spawner(std::string _name, GameObject* _parent);
	virtual void Start();
	virtual void Tick(float _DeltaTime);

private:
		float		m_spawnTimer;
		float		m_spawnRate;
		int			m_spawnCount;
		int			m_spawnLimit;
		GameObject* m_player;
		glm::vec2	m_size = glm::vec2( 20 , 7 );

		std::vector<frost::ECS::GameObject*> m_SpawnedObjects;
		float lastSpawnTime;
		float spawnRate;

		void Spawn(glm::vec2 _spawnLocation);

		float GetRandomInRange(float min, float max);
		
};


