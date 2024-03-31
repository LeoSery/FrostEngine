#pragma once

/*!
* \file Window.h
* 
* \brief Header file for the Export class.
*/

#include "Export.h"

#include <glm/glm.hpp>
#include <memory>

#pragma region Forward Declarations
namespace frost
{
	class Application;
}

namespace frost::render
{
	class RenderDevice;
}

namespace frost::editor
{
	class Editor;
}

namespace frost::core
{
	class Input;
}
#pragma endregion

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
		friend class Editor;
		friend class RenderDevice;
		friend class Application;
		friend class Input;

	protected:

		// Structs

		/*!
		* \struct S_WindowProperties
		*
		* \brief This struct holds the properties of the window.
		*
		* \details This struct holds the title, size, and full screen
		*/
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
		bool PollEvents();

	public:

		/*!
		* \brief Get current window.
		* 
		* \fn Window::GetInternal() const;
		* 
		* \return The pointer to the window.
		*/
		void* GetInternal() const;

	private:
		struct Internal;
		std::unique_ptr<Internal> m_impl;
	};
}
