#include "Render/RenderDevice.h"
#include "Core/Window.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

namespace frost::core
{
	RenderDevice* RenderDevice::m_instance = nullptr;

	struct RenderDevice::Internal
	{
		GLFWwindow* window = nullptr;
		std::vector<VertexArrayObject> VaoToRender;
	};

	RenderDevice::RenderDevice()
		:m_internal(new Internal)
	{}

	RenderDevice::~RenderDevice()
	{

		glDeleteVertexArrays(1, &m_vao);
		glfwTerminate();

	}

	RenderDevice* RenderDevice::Init(const Window* _window)
	{
		m_internal->window = reinterpret_cast<GLFWwindow*>(_window->GetInternal());
		glewInit();

		
		m_shaderProgram.InitShader("default.vert", "default.frag");// set shaderProgram of used shader

		//for alpha blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//PickUp Position of the shader in memory
		m_positionLocation = glGetUniformLocation(m_shaderProgram.m_gl_ID, "uPosition");
		m_rotationLocation = glGetUniformLocation(m_shaderProgram.m_gl_ID, "uRotation");
		m_scaleLocation = glGetUniformLocation(m_shaderProgram.m_gl_ID, "uScale");
		m_aspectRatioLocation = glGetUniformLocation(m_shaderProgram.m_gl_ID, "uAspectRatio");
		m_texture = glGetUniformLocation(m_shaderProgram.m_gl_ID, "uTexture");

		return m_instance;
	}

	RenderDevice* RenderDevice::GetInstance()
	{
		if (!m_instance)
		{
			m_instance = new RenderDevice();
		}

		return m_instance;
	}

	void RenderDevice::Update()
	{

		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		m_shaderProgram.Enable();

		int w, h;
		glfwGetWindowSize(m_internal->window, &w, &h);
		glProgramUniform1f(m_shaderProgram.m_gl_ID, m_aspectRatioLocation, float(w) / float(h));

		for (int i = 0; i < GetVaoToRender().size(); i++)
		{
			GetVaoToRender()[i].Bind();
			//On Dit au shader les uniform du VAO
			glProgramUniform2f(m_shaderProgram.m_gl_ID, m_positionLocation, GetVaoToRender()[i].GetLocation().x, GetVaoToRender()[i].GetLocation().y);
			glProgramUniform1f(m_shaderProgram.m_gl_ID, m_rotationLocation, GetVaoToRender()[i].GetRotation());
			glProgramUniform2f(m_shaderProgram.m_gl_ID, m_scaleLocation, GetVaoToRender()[i].GetScale().x, GetVaoToRender()[i].GetScale().y);
			glProgramUniform1i(m_shaderProgram.m_gl_ID, m_texture, 0);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		}
		ClearVaosToRender();

	}
	void RenderDevice::AddVAO(VertexArrayObject _newVao)
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

