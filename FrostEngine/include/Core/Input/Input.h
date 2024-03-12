#pragma once

#include "Core/Export.h"
#include "IInputable.h"


#include <GLFW/glfw3.h>

#include <functional>
#include <string>
#include <memory>
#include <vector>
#include <map>




namespace frost::core 
{
	class Window;

	class FROST_ENGINE_API Input : public IInputable
	{
		

	protected: 
		static Input* m_Instance;

	public:
		// Constructor and Destructors
        Input(Input& other) = delete;
        void operator=(const Input&) = delete;
		explicit Input();

		// Instance
        static Input* GetInstance();

		// Methods
		Input* init(Window* _window);

		//forward Declaration for pimple idiom BUT IT'S NOT WORKING
	private:

		struct Internal
		{
			GLFWwindow* window = nullptr;
		};

		std::unique_ptr<Internal> m_internal;

		std::map<int, std::string> KeyBind; //key = Action
		std::map<std::string,std::vector<std::function<void()>> > ActionBind; //Action = Function to call

		void AddAction(std::string ActionName);

		bool AddKeyToAction(int key, std::string ActionName);//return true if succesfully added

	public:

		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	};
}