#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cerrno>
#include <string>

namespace frost::core
{
	class Shader
	{
	public:

		// Constructor
		Shader();

		// Methods
		void InitShader(const char* _VertexFile, const char* _FragmentFile);
		void Enable();
		void Delete();

		// Getters
		GLuint m_gl_ID; // Reference ID of the ShaderClass Program

		[[nodiscard]] std::string ReadShaderFile(const char* _Filename);
	};
}
