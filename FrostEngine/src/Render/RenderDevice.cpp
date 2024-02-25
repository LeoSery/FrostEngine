#include "Render/RenderDevice.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Core/Window.h"



namespace frost::core 
{

	struct RenderDevice::Internal
	{
		GLFWwindow* window = nullptr;
		std::vector<VertexArrayObject> VaoToRender;
	};

	RenderDevice::RenderDevice(Window& _window)
		:m_internal(new Internal), TestTex("T_PlaceHolder.png")
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
 
		shaderProgram.InitShader("default.vert", "default.frag");

		TestTex.Bind();

		//PickUp Position of the shader in memory
		positionLocation    = glGetUniformLocation(shaderProgram.m_gl_ID, "uPosition");
		rotationLocation    = glGetUniformLocation(shaderProgram.m_gl_ID, "uRotation");
		scaleLocation       = glGetUniformLocation(shaderProgram.m_gl_ID, "uScale");
		aspectRatioLocation = glGetUniformLocation(shaderProgram.m_gl_ID, "uAspectRatio");
		texture				= glGetUniformLocation(shaderProgram.m_gl_ID, "uTexture");

	}
	void RenderDevice::Update()
	{

		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.Enable();

		int w, h;
		glfwGetWindowSize(m_internal->window, &w, &h);
		glProgramUniform1f(shaderProgram.m_gl_ID, aspectRatioLocation, float(w) / float(h));

		for (int i = 0; i < GetVaoToRender().size(); i++)
		{
			GetVaoToRender()[i].Bind();
			//On Dit au shader les uniform du VAO
			glProgramUniform2f(shaderProgram.m_gl_ID, positionLocation, GetVaoToRender()[i].GetLocation().x , GetVaoToRender()[i].GetLocation().y);
			glProgramUniform1f(shaderProgram.m_gl_ID, rotationLocation, GetVaoToRender()[i].GetRotation());
			glProgramUniform2f(shaderProgram.m_gl_ID, scaleLocation, GetVaoToRender()[i].GetScale().x, GetVaoToRender()[i].GetScale().y);
			glProgramUniform1i(shaderProgram.m_gl_ID, texture, 0);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		}
		ClearVaosToRender();
		
	}
	void RenderDevice::AddVao(VertexArrayObject _newVao)
	{
		m_internal->VaoToRender.push_back(_newVao);
	}
	void RenderDevice::ClearVaosToRender()
	{
		m_internal->VaoToRender.clear();
	}
	std::vector<VertexArrayObject> RenderDevice::GetVaoToRender()
	{
		return m_internal->VaoToRender;
	}
}

