#include "Core/Input/Input.h"
#include "Core/Window.h"
#include <iostream>


namespace frost::core
{
	Input* Input::m_Instance = nullptr;

	Input::Input() : m_internal(new Internal)
	{}

	Input* Input::GetInstance()
	{
		if (m_Instance == nullptr) {
			m_Instance = new Input;
		}
		return m_Instance;
	}

	Input* Input::init(Window* _window)
	{

		m_internal->window = static_cast<GLFWwindow*>(_window->GetInternal());
		glfwSetKeyCallback(m_internal->window,key_callback);
		return m_Instance;
	}

	void Input::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		key;
		scancode;
		action;
		mods;
		window;

		
	}

	bool Input::AddKeyToAction(int key, std::string ActionName)
	{
		key;
		ActionName;
		return false;
	}

	void Input::AddAction(std::string ActionName)
	{
	}

}
