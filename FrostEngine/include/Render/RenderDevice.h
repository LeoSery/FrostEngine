#pragma once

#include <memory>

#include "Core/Window.h"

namespace frost::core {
	
	class RenderDevice
	{

		//forward Declaraction for pimple idiom
	private:
		struct Internal;
		std::unique_ptr<Internal> m_internal;
	
	public:
	
		explicit RenderDevice(const Window& _window);
		~RenderDevice();


	
	};

}

