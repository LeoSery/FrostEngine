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

		/*!
		* \brief Initialize the Shader.
		* \details Initialize the Shader with the given Vertex and Fragment Shader files.
		* \n The function will read the files and create the Shader.
		* \n then link it and save the id used to bind the shader when rendering.
		* 
		* \fn InitShader(const char* _VertexFile, const char* _FragmentFile)
		* \param _VertexFile The path to the Vertex Shader file.
		*/
		void InitShader(const char* _VertexFile, const char* _FragmentFile);

		/*!
		* \brief this method Bind the Shader to the OpenGL context.
		* \fn Enable()
		*/
		void Enable();

		/*!
		* \brief this method Delete the Shader from the OpenGL context.
		* \fn Delete()
		*/
		void Delete();


		GLuint m_gl_ID; // Reference ID of the ShaderClass Program

	private:
		[[nodiscard]] std::string ReadShaderFile(const char* _Filename);
	};
}
