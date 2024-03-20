#pragma once
#include "FrostEngine.h"
#include "ECS/Entity/GameObject.h"

class frost::ECS::GameObject;

class TestInput : public frost::ECS::GameObject
{
public:	
	static TestInput* New(std::string _name);
	TestInput(std::string _name);
	void Begin();

private:
	void Print();

	float A = 0;
};

