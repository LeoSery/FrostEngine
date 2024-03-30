#pragma once

/*!
* \file Shader.h
* 
* \brief Header file for the Shader class.
*/

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cerrno>
#include <string>

/*!
* \namespace frost::render
*
* The namespace for FrostEngine's rendering functionalities.
*/
namespace frost::render
{
	/*!
	* \class Shader
	* 
	* \brief The class that manages the Shader of the FrostEngine.
	* 
	* \details read, create and manage the Shader of the FrostEngine.
	*/
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
