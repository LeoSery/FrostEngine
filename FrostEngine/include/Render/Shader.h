#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

namespace frost::core
{
	

	class Shader
	{

	public:

		Shader();

		void InitShader(const char* _vertexFile, const char* _fragmentFile);

		// Reference ID of the ShaderClass Program
		GLuint m_gl_ID;

		void Enable();
		void Delete();

		std::string ReadShaderFile(const char* _filename);

	};

}