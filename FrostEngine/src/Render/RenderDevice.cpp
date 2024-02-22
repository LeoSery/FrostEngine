#include "Render/RenderDevice.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Core/Window.h"
#include "Render/VertexArrayObject.h"

namespace frost::core 
{

	struct RenderDevice::Internal
	{
		GLFWwindow* window = nullptr;
	};

	RenderDevice::RenderDevice(Window& _window)
		:m_internal(new Internal)
	{
		m_internal->window = static_cast<GLFWwindow*>(_window.GetInternal());
		glewInit();

	}

	RenderDevice::~RenderDevice()
	{

		glDeleteVertexArrays(1, &vao);

		glfwTerminate();

	}

	void RenderDevice::test()
	{
		//TEST
		float vertices[] = { 
					-0.5f,  0.5f, /*Color*/0.5f, 0.0f, 0.0f,
					-0.5f, -0.5f, /*Color*/0.0f, 1.0f, 1.0f,
					 0.5f, -0.5f, /*Color*/0.5f, 1.0f, 0.0f,
					 0.5f,  0.5f, /*Color*/1.0f, 0.8f, 1.0f
		};

		unsigned int indices[] = { 0, 1, 2, 0, 2, 3 };



		unsigned int buffers[2];
		/*buffer[0] = vertices data	== VBO <- I WAS LOOKING FOR IT , IM SO DUMB SMH
		  buffer[1] = indices data	== IBO		*/

		glCreateBuffers(2, buffers); //Hey open gl i need 2 IDS to store things
		glNamedBufferStorage(buffers[0], sizeof(vertices), vertices, 0); //Buffer 0 = VBO
		glNamedBufferStorage(buffers[1], sizeof(indices), indices, 0);
 
		shaderProgram.InitShader("default.vert", "default.frag");

		//PickUp Position of the shader in memory
		positionLocation    = glGetUniformLocation(shaderProgram.ID, "uPosition");
		rotationLocation    = glGetUniformLocation(shaderProgram.ID, "uRotation");
		scaleLocation       = glGetUniformLocation(shaderProgram.ID, "uScale");
		aspectRatioLocation = glGetUniformLocation(shaderProgram.ID, "uAspectRatio");
		

		VertexArrayObject Hehe(buffers);
		Hehe.Bind();
	}
	void RenderDevice::Update()
	{

		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//glBindVertexArray(vao);
		//Bind vao

		shaderProgram.Enable();

		int w, h;
		glfwGetWindowSize(m_internal->window, &w, &h);


		glProgramUniform1f(shaderProgram.ID, aspectRatioLocation, float(w) / float(h));

		//Draw call
		int numObjects = 1;
		for (int i = 0; i < numObjects; i++)
		{
			glProgramUniform2f(shaderProgram.ID, positionLocation, 0.2f, 0.0f);
			glProgramUniform1f(shaderProgram.ID, rotationLocation, 0.f);
			glProgramUniform2f(shaderProgram.ID, scaleLocation, 1.0f, 1.0f);
			

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		}
		
		//Remove the Program from using
		glUseProgram(0);
		//Unbind the vao
		//glBindVertexArray(0);
	}
}

