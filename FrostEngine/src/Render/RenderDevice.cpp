#include "Render/RenderDevice.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Core/Window.h"

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

	}

	void RenderDevice::test()
	{
		//TEST
		float vertices[] = { 
					-0.5f,  0.5f, /*Color*/1.0f, 0.0f, 0.0f,
					-0.5f, -0.5f, /*Color*/0.0f, 0.0f, 1.0f,
					 0.5f, -0.5f, /*Color*/0.0f, 1.0f, 0.0f,
					 0.5f,  0.5f, /*Color*/1.0f, 1.0f, 1.0f
		};

		unsigned int indices[] = { 0, 1, 2, 0, 2, 3 };

		//Shaders sources
		const char* vsSrc = R"(#version 460 core
								layout(location = 0) in vec2 aPos;
								layout(location = 1) in vec3 aColor;
								out vec3 vColor;
								void main()
								{
									gl_Position = vec4(aPos, 0.0, 1.0);
									vColor = aColor;
								})";

		const char* fsSrc = R"(#version 460 core
								in vec3 vColor;
								layout(location = 0) out vec4 oFragColor;
								void main()
								{
									oFragColor = vec4(vColor, 1.0);
								})";

		//memory allocation in VRAM + adding data
		unsigned int buffers[2];
		glCreateBuffers(2, buffers);
		glNamedBufferStorage(buffers[0], sizeof(vertices), vertices, 0);
		glNamedBufferStorage(buffers[1], sizeof(indices), indices, 0);



		//Geometry
		
		glCreateVertexArrays(1, &vao);

		glVertexArrayVertexBuffer(vao, 0, buffers[0], 0 /*Offset par rapport au debut du buffer*/, 5 * sizeof(float) /*Data par vertice*/);

		//On active l'attribut 0 du VAO
		glEnableVertexArrayAttrib(vao, 0);
		glVertexArrayAttribBinding(vao, 0, 0);
		glVertexArrayAttribFormat(vao, 0, 2 /*L'attribut a une taille de deux GL_FLOAT*/, GL_FLOAT, GL_FALSE, 0);

		//On active l'attribut 1 du VAO
		glEnableVertexArrayAttrib(vao, 1);
		glVertexArrayAttribBinding(vao, 1, 0); //On Bind l'attribut 1 au buffer 0 qu'on lui a passer au dessus
		glVertexArrayAttribFormat(vao, 1, 3 /*L'attribut a une taille de deux GL_FLOAT*/ , GL_FLOAT, GL_FALSE, 2 * sizeof(float)); // et un offset de 2

		glVertexArrayElementBuffer(vao, buffers[1]);// This is to link vertices buffer[1] is the buffer that have order to draw triangle

		//Create Vertex shader from src and compile it
		vs = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vs, 1, &vsSrc, nullptr);
		glCompileShader(vs);

		//Create Fragment shader from src and compile it
		fs = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fs, 1, &fsSrc, nullptr);
		glCompileShader(fs);

		//Create program, attach it shaders and link it
		sp = glCreateProgram();
		glAttachShader(sp, vs);
		glAttachShader(sp, fs);
		glLinkProgram(sp);
	}
	void RenderDevice::Update()
	{


		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Bind vao
		glBindVertexArray(vao);
		//Use program (with vao)
		glUseProgram(sp);
		//Draw call
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		//Remove the Program from using
		glUseProgram(0);
		//Unbind the vao
		glBindVertexArray(0);

		//swap frame buffers
		//glfwSwapBuffers(m_internal->window);
	}
}

