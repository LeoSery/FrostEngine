#pragma once

#include "Core/Export.h"
#include <memory>

#include <glm/glm.hpp>

namespace frost::core
{
	class FROST_ENGINE_API Window
	{	
	public:

		struct WindowProperties
		{
			const char* Title;
			glm::ivec2 Size;
		};

		explicit Window(WindowProperties Properties);
		~Window();
	
		//this Function need to be called in the main loop of the application
		bool PollEvents();

	private:
		//pimple idiom ?
		struct Internal;
		std::unique_ptr<Internal> m_impl;
	};
}
