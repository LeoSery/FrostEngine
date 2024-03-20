#include "Core/Input/Input.h"
#include "Utils/Logger.h"
#include "Core/Window.h"

#include <GLFW/glfw3.h>
#include <iostream>

namespace frost::core
{
	Input* Input::m_instance = nullptr;

	struct Input::Internal
	{
		GLFWwindow* window = nullptr;
	};

	Input::Input() : m_internal(new Internal)
	{}

	Input::~Input()
	{
		delete m_instance;
	}

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
			switch (action)
			{

			case 0: //Released

				m_instance->CallAction(m_instance->KeyBind.at(key), action);
				if (m_instance->KeyPressed.contains(key))
				{
					m_instance->KeyPressed.at(key) = false;
				}
				else
				{
					m_instance->KeyPressed.insert({ key , false });
				}
 				break;

			case 1: //Pressed

				m_instance->CallAction(m_instance->KeyBind.at(key), action);

				if (m_instance->KeyPressed.contains(key))
				{
					m_instance->KeyPressed.at(key) = true;
				}
				else
				{
					m_instance->KeyPressed.insert({ key , true });
				}

				break;

			default:
				break;
			}
		}
		
	}

	void Input::Update()
	{

		for (std::pair<int, bool> elem : KeyPressed)
		{
			if (KeyBind.contains(elem.first) && elem.second)
			{
				CallAction(KeyBind.at(elem.first), ActionType::OnGoing);
			}
		}
	}

	void Input::AddAction(std::string _actionName)
	{
		if (! m_instance->ActionBind.contains(_actionName))
		{
			std::pair<std::string, std::vector<ObjectFunction>> toadd(_actionName, std::vector<ObjectFunction>());
			m_instance->ActionBind.insert(toadd);
		}
		else
		{
			frost::utils::Logger::LogWarning("Can't add " + _actionName + " already exists");
		}
	}

	bool Input::AddActionToKey(Key _key, std::string _actionName)
	{

		if (m_instance->ActionBind.contains(_actionName))
		{
			if (m_instance->KeyBind.contains(_key))
			{
				m_instance->KeyBind.at(_key) = _actionName;
			}
			else
			{
				std::pair<int, std::string> toadd(_key, _actionName);
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

	void Input::BindFunctionToAction(std::string _actionName, frost::ECS::GameObject* _object, std::function<void()> _functionToCall, ActionType _onWhat)
	{
		if (m_instance->ActionBind.contains(_actionName))
		{
			switch (_onWhat)
			{
			case frost::core::Input::Release:
				m_instance->ActionBind.at(_actionName).FunctionReleased.push_back({ _object , _functionToCall });
				break;
			case frost::core::Input::Press:
				m_instance->ActionBind.at(_actionName).FunctionPressed.push_back({ _object , _functionToCall });
				break;
			case frost::core::Input::OnGoing:
				m_instance->ActionBind.at(_actionName).FunctionOnGoing.push_back({ _object , _functionToCall });
				break;

			default:
				break;
			}
		}
		else
		{
			frost::utils::Logger::LogError("Action " + _actionName + " does not exist");
		}

	}

	void Input::CallAction(std::string _actionToCall , int _action)
	{
		
		std::vector<ObjectFunction>* ObjectsFunc;
		switch (_action)
		{
		case 0:
			ObjectsFunc = &m_instance->ActionBind.at(_actionToCall).FunctionReleased;
			break;
		case 1:
			ObjectsFunc = &m_instance->ActionBind.at(_actionToCall).FunctionPressed;
			break;
		case 2:
			ObjectsFunc = &m_instance->ActionBind.at(_actionToCall).FunctionOnGoing;
			break;
		default:
			return;
		}

		for (size_t i = 0; i < ObjectsFunc->size(); i++)
		{
			if (ObjectsFunc->at(i).Object != nullptr)
			{
				ObjectsFunc->at(i).Function();
			}
			else
			{
				ObjectsFunc->erase(ObjectsFunc->begin() + i);
			}
		}
	}

	void Input::RemoveAction(std::string _actionName)
	{
		if (m_instance->ActionBind.contains(_actionName))
		{
			m_instance->ActionBind.erase(_actionName);
		}
		else
		{
			frost::utils::Logger::LogWarning("Unable to remove action : " + _actionName);
		}
	}

}
