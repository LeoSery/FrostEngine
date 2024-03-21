#pragma once

#include "FrostEngine.h"

class Player : public frost::ECS::GameObject
{
public:
	static Player* New(std::string _name, GameObject* _parent);
	Player(std::string _name, GameObject* _parent);
	virtual void Start();

private:
	void MoveForward();
	void MoveBackward();
	void MoveLeft();
	void MoveRight();
	float A = 0;
};

