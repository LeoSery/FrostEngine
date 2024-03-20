#include "TestInput.h"
#include "Core/Input/Input.h"
using Input = frost::core::Input;

TestInput::TestInput(std::string _name)
	: GameObject(_name)
{
}

TestInput* TestInput::New(std::string _name)
{
	TestInput* result = new TestInput(_name);
	result->Init();
	return result;
}

void TestInput::Begin()
{
	Input::GetInstance()->AddAction("NewAction");
	Input::GetInstance()->AddActionToKey(Input::Key::A, "NewAction");
	Input::GetInstance()->BindFunctionToAction("NewAction", this, [this]() {Print(); } , Input::ActionType::OnGoing);
}

void TestInput::Print()
{
	A = A + 0.1f;
	std::cout << A << std::endl;
}
