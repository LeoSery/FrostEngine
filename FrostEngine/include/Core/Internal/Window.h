#pragma once

/*!
* \file Window.h
* 
* \brief Header file for the Export class.
*/

#include "Export.h"

#include <glm/glm.hpp>
#include <memory>

/*!
* \namespace frost::core
*
* \brief The namespace for FrostEngine's core functionalities.
*/
namespace frost::core
{
	/*!
	* \class Window
	* 
	* \brief The class for the window of the application.
	* 
	* \details This class is responsible for controlling the engine
	* window while the engine is running. It contains information
	* related to this window and also handles events triggered in it.
	*/
	class FROST_ENGINE_API Window
	{
	public:

		struct S_WindowProperties
		{
			const char* title;
			glm::ivec2 size;
			bool fullScreen = false;
		};

		// Constructor and Destructor
		explicit Window(S_WindowProperties _Properties);
		~Window();

		// Methods
		bool PollEvents(); //this Function need to be called in the main loop of the application

		// Getters
		void* GetInternal() const;

	private:
		struct Internal;
		std::unique_ptr<Internal> m_impl;
	};
}
