#include "Render/RenderDevice.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"


namespace frost::core {
	
	struct RenderDevice::Internal
	{
		GLFWwindow* window = nullptr;
	};

	RenderDevice::RenderDevice(const Window& _window)
		: m_internal(std::make_unique<Internal>())
	{
		_window;
		m_internal->window = reinterpret_cast<GLFWwindow*>(m_internal->window);
	}

	RenderDevice::~RenderDevice()
	{
	}
}

