#include "Core/Window.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

namespace frost::core
{
	struct Window::Impl
	{
		GLFWwindow* window = nullptr;
	};

	Window::Window(WindowProperties Properties)
		: m_impl(std::make_unique<Impl>())
	{

		if (!glfwInit())
		{
			fprintf(stderr, "Failed to initialize GLFW\n");
			return;
		}

		glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

#ifndef NDEBUG
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#else /* !NDEBUG */
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_FALSE);
#endif /* !NDEBUG */

		glfwWindowHint(GLFW_SRGB_CAPABLE, GL_TRUE);
		glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE); //Double Buffering

		m_impl->window = glfwCreateWindow(
			Properties.Size.x,
			Properties.Size.y,
			Properties.Title,
			NULL, NULL);

		if (m_impl->window == nullptr)
		{
			fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
			glfwTerminate();
		}

		glfwMakeContextCurrent(m_impl->window);
		// Ensure we can capture the escape key being pressed below
		glfwSetInputMode(m_impl->window, GLFW_STICKY_KEYS, GL_TRUE);

	}

	Window::~Window()
	{
		glfwDestroyWindow(m_impl->window);
	}

	bool Window::PollEvents()
	{
		//TODO: Move this to a renderer class

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw nothing, see you in tutorial 2 !

		// Swap buffers
		glfwSwapBuffers(m_impl->window);
		glfwPollEvents();

		return glfwGetKey(m_impl->window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
			glfwWindowShouldClose(m_impl->window) == 0;
	}

}