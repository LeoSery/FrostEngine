#include "Core/Input/Input.h"
#include "Core/Window.h"

#include "Utils/Logger.h"

#include <iostream>


namespace frost::core
{
	Input* Input::m_instance = nullptr;

	Input::Input() : m_internal(new Internal)
	{}

	Input* Input::GetInstance()
	{
		if (m_instance == nullptr) {
			m_instance = new Input;
		}
		return m_instance;
	}

	Input* Input::init(Window* _window)
	{
		m_internal->window = static_cast<GLFWwindow*>(_window->GetInternal());
		glfwSetKeyCallback(m_internal->window,key_callback);
		return m_instance;
	}

	void Input::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		key;
		scancode;
		action;
		mods;
		window;

		if (m_instance->KeyBind.contains(key))
		{
			m_instance->CallAction(m_instance->KeyBind.at(key));
		}
	}

	void Input::AddAction(std::string _actionName)
	{
		if (! m_instance->ActionBind.contains(_actionName))
		{
			std::pair<std::string, std::vector<std::function<void()>>> toadd(_actionName, std::vector<std::function<void()>>());
			m_instance->ActionBind.insert(toadd);
		}
		else
		{
			frost::utils::Logger::LogWarning("Can't add " + _actionName + " already exists");
		}
	}

	bool Input::AddActionToKey(int key, std::string _actionName)
	{

		if (m_instance->ActionBind.contains(_actionName))
		{
			if (m_instance->KeyBind.contains(key))
			{
				m_instance->KeyBind.at(key) = _actionName;
			}
			else
			{
				std::pair<int, std::string> toadd(key, _actionName);
				m_instance->KeyBind.insert(toadd);
			}
			return true;
		}
		else
		{
			frost::utils::Logger::LogWarning("Action " + _actionName + " does not exist");
		}
		return false;
	}

	void Input::AddFunctionToAction(std::string _actionName, std::function<void()> _functionToCall)
	{
		if (m_instance->ActionBind.contains(_actionName))
		{
			m_instance->ActionBind.at(_actionName).push_back(_functionToCall);
		}
		else
		{
			frost::utils::Logger::LogError("Action " + _actionName + " does not exist");
		}
	}

	void Input::CallAction(std::string _actionToCall)
	{
		for (size_t i = 0; i < m_instance->ActionBind.at(_actionToCall).size(); i++)
		{
			m_instance->ActionBind.at(_actionToCall).at(i)();
		}
	}

}
