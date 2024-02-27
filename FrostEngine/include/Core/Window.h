#pragma once

#include "Core/Export.h"

#include <glm/glm.hpp>
#include <memory>

namespace frost::core
{
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
		void* GetInternal();

	private:
		//pimple idiom ?
		struct Internal;
		std::unique_ptr<Internal> m_impl;
	};
}
