#pragma once

/*!
* \file Input.h
* 
* \brief Header file for the Input class.
*/

#include "Core/Internal/Export.h"

#include <functional>
#include <string>
#include <memory>
#include <vector>
#include <map>

/*!
* \forward declaration of GLFWwindow and GameObject.
*/
struct	GLFWwindow;
namespace frost::ECS
{
	class GameObject;
}

/*!
* \namespace frost::core
* 
* \brief The namespace for FrostEngine's core functionalities.
*/
namespace frost::core
{
	class Window;

	/*!
	* \class Input
	* 
	* \brief This class lets you create actions, so you can bind inputs to actions.
	* 
	* \details This class can be used to create/delete custom actions, to bind and configure
	* a button, and to associate methods with this custom action so that they are called when the
	* action is triggered by pressing the associated button.
	*/
	class FROST_ENGINE_API Input
	{
		friend class Application;

	public:

		// Constructor and Destructors
		Input(Input& other) = delete;
		void operator=(const Input&) = delete;
		explicit Input();
		~Input();

		// Instance
		static Input* GetInstance();

		/*!
		* \enum E_Key
		* 
		* \brief Enum for the key codes.
		* 
		* \details This enum contains all the key codes that can be used to bind an action to a key.
		*/
		enum E_Key
		{
			SPACE = 32,
			APOSTROPHE = 39,/* ' */
			COMMA = 44,/* , */
			MINUS = 45,/* - */
			PERIOD = 46,/* . */
			SLASH = 47,/* / */
			num_0 = 48,
			num_1 = 49,
			num_2 = 50,
			num_3 = 51,
			num_4 = 52,
			num_5 = 53,
			num_6 = 54,
			num_7 = 55,
			num_8 = 56,
			num_9 = 57,
			SEMICOLON = 59,/* ; */
			EQUAL = 61,/* = */
			A = 65,
			B = 66,
			C = 67,
			D = 68,
			E = 69,
			F = 70,
			G = 71,
			H = 72,
			I = 73,
			J = 74,
			K = 75,
			L = 76,
			M = 77,
			N = 78,
			O = 79,
			P = 80,
			Q = 81,
			R = 82,
			S = 83,
			T = 84,
			U = 85,
			V = 86,
			W = 87,
			X = 88,
			Y = 89,
			Z = 90,
			LEFT_BRACKET = 91,/* [ */
			BACKSLASH = 92,/* \ */
			RIGHT_BRACKET = 93,/* ] */
			GRAVE_ACCENT = 96,/* ` */
			WORLD_1 = 161, /* non-US #1 */
			WORLD_2 = 162, /* non-US #2 */
			ESCAPE = 256,
			ENTER = 257,
			TAB = 258,
			BACKSPACE = 259,
			INSERT = 260,

			RIGHT = 262,
			LEFT = 263,
			DOWN = 264,
			UP = 265,
			PAGE_UP = 266,
			PAGE_DOWN = 267,
			HOME = 268,
			END = 269,
			CAPS_LOCK = 280,
			SCROLL_LOCK = 281,
			NUM_LOCK = 282,
			PRINT_SCREEN = 283,
			PAUSE = 284,
			F1 = 290,
			F2 = 291,
			F3 = 292,
			F4 = 293,
			F5 = 294,
			F6 = 295,
			F7 = 296,
			F8 = 297,
			F9 = 298,
			F10 = 299,
			F11 = 300,
			F12 = 301,
			F13 = 302,
			F14 = 303,
			F15 = 304,
			F16 = 305,
			F17 = 306,
			F18 = 307,
			F19 = 308,
			F20 = 309,
			F21 = 310,
			F22 = 311,
			F23 = 312,
			F24 = 313,
			F25 = 314,
			KP_0 = 320,
			KP_1 = 321,
			KP_2 = 322,
			KP_3 = 323,
			KP_4 = 324,
			KP_5 = 325,
			KP_6 = 326,
			KP_7 = 327,
			KP_8 = 328,
			KP_9 = 329,
			KP_DECIMAL = 330,
			KP_DIVIDE = 331,
			KP_MULTIPLY = 332,
			KP_SUBTRACT = 333,
			KP_ADD = 334,
			KP_ENTER = 335,
			KP_EQUAL = 336,
			LEFT_SHIFT = 340,
			LEFT_CONTROL = 341,
			LEFT_ALT = 342,
			LEFT_SUPER = 343,
			RIGHT_SHIFT = 344,
			RIGHT_CONTROL = 345,
			RIGHT_ALT = 346,
			RIGHT_SUPER = 347
		};

		/*!
		* \enum E_ActionType
		* 
		* \brief Enum for the action types.
		* 
		* \details This enum contains all the action types that can be used to bind a function to an action.
		* 
		* \note Release = 0, Press = 1, OnGoing = 2
		*/
		enum E_ActionType
		{
			Release = 0,
			Press = 1,
			OnGoing = 2
		};

		/*!
		* \struct S_ObjectFunction
		* 
		* \brief Structure for the binding of a function to an object.
		* 
		* \details This structure contains the object and the function to call when the action is triggered.
		*/
		struct S_ObjectFunction
		{
			frost::ECS::GameObject* Object;
			std::function<void()> Function;
		};

		/*!
		* \struct S_Functions
		* 
		* \brief Structure for the binding of functions to an action.
		* 
		* \details This structure contains the functions to call when the action is triggered.
		*/
		struct S_Functions
		{
			std::vector<S_ObjectFunction> FunctionPressed;
			std::vector<S_ObjectFunction> FunctionReleased;
			std::vector<S_ObjectFunction> FunctionOnGoing;
		};

		// Methods

		/*!
		* \brief Initialize the Input class.
		* 
		* \details Define the window to initialize the input class. 
		* bind the key_callback function to the window.
		* 
		* \fn Input* Input::init(Window* _window)
		* 
		* \param _window The window to initialize the input class.
		* 
		* \return The initialized input class.
		*/
		Input* init(Window* _window);

		/*!
		* \brief Creates an action in the game.
		* 
		* \details This function creates an action in the game that can be binded to a keys.
		* 
		* \fn void Input::AddAction(std::string _actionName)
		*/
		void AddAction(std::string _actionName);

		/*!
		* \brief Binds an action to a key.
		* 
		* \details This function binds an action to a key.
		* 
		* \fn bool Input::AddActionToKey(E_Key _key, std::string _actionName)
		* 
		* \param _key The key to bind the action to.
		* \param _actionName The action to bind to the key.
		* 
		* \return True if the action was successfully binded to the key, false otherwise.
		*/
		bool AddActionToKey(E_Key _key, std::string _actionName);

		/*!
		* \brief Binds a function to an action.
		* 
		* \details This function binds a function to an action.
		* 
		* \fn void Input::BindFunctionToAction(std::string _actionName, frost::ECS::GameObject* Object, std::function<void()> _functionToCall, E_ActionType _onWhat)
		* 
		* \param _actionName The action to bind the function to.
		* \param Object The object to bind the function to.
		* \param _functionToCall The function to call when the action is triggered.
		* \param _onWhat The type of action to bind the function to.
		*/
		void BindFunctionToAction(std::string _actionName, frost::ECS::GameObject* Object, std::function<void()> _functionToCall, E_ActionType _onWhat);

		/*!
		* \brief Calls the action.
		* 
		* \details call a specific action, an trigger the function binded to it.
		* 
		* \fn void Input::CallAction(std::string _actionToCall, int _action)
		* 
		* \param _actionToCall The action to call.
		* \param _action The action type.
		*/
		void CallAction(std::string _actionToCall, int _action);

		/*!
		* \brief Removes an action.
		* 
		* \details This function removes an action from the game.
		* 
		* \fn void Input::RemoveAction(std::string _actionName).
		* 
		* \param _actionName The action to remove.
		*/
		void RemoveAction(std::string _actionName);

	protected:

		static Input* m_instance;
		void Update();

	private:

		struct Internal;
		std::unique_ptr<Internal> m_internal;

		std::map<int, std::string> KeyBind;
		std::map<std::string, S_Functions> ActionBind;
		std::map<int, bool> KeyPressed;

		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	};
}
