#pragma once

#include "Core/Export.h"

#include <GLFW/glfw3.h>
#include <functional>
#include <string>
#include <memory>
#include <vector>
#include <map>

namespace frost::core 
{
	class Window;

	class FROST_ENGINE_API Input
	{
	public:
		// Constructor and Destructors
        Input(Input& other) = delete;
        void operator=(const Input&) = delete;
		explicit Input();

		// Instance
        static Input* GetInstance();

		// Methods
		Input* init(Window* _window);
		void AddAction(std::string _actionName);
		bool AddActionToKey(int key, std::string _actionName);//return true if succesfully added
		void AddFunctionToAction(std::string _actionName, std::function<void()> _functionToCall);
		void CallAction(std::string _actionToCall);

	protected:
		static Input* m_instance;

		//forward Declaration for pimple idiom BUT IT'S NOT WORKING
	private:

		struct Internal
		{
			GLFWwindow* window = nullptr;
		};

		std::unique_ptr<Internal> m_internal;
		std::map<int, std::string> KeyBind; //key = Action
		std::map<std::string,std::vector<std::function<void()>> > ActionBind; //Action = Function to call

		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	};
}
