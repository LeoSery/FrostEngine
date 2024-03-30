#pragma once
#include "ECS/Entity/GameObject.h"

class Spawner : public frost::ECS::GameObject
{
	public:
	static Spawner* New(std::string _name, GameObject* _parent);
	Spawner(std::string _name, GameObject* _parent);
	virtual void Start();
	virtual void Tick(float _DeltaTime);

	private:
		float m_SpawnTimer;
		float m_SpawnRate;
		int m_SpawnCount;
		int m_SpawnLimit;

};

