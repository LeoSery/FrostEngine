#include "Render/Shader.h"

#include <filesystem>

namespace frost::core
{
	Shader::Shader()
	{
	}

	void Shader::InitShader(const char* _vertexFile, const char* _fragmentFile)
	{
		//this return a string but we need a const char*
		std::string vertShaderSrc = ReadShaderFile(_vertexFile);
		std::string fragShaderSrc = ReadShaderFile(_fragmentFile);

		const char* vertShader = vertShaderSrc.c_str();
		const char* fragShader = fragShaderSrc.c_str();

		//Create Vertex shader from src and compile it
		GLuint vs = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vs, 1, &vertShader, nullptr);
		glCompileShader(vs);

		//Create Fragment shader from src and compile it
		GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fs, 1, &fragShader, nullptr);
		glCompileShader(fs);

		//Create program, attach it shaders and link it
		m_gl_ID = glCreateProgram();
		glAttachShader(m_gl_ID, vs);
		glAttachShader(m_gl_ID, fs);
		glLinkProgram(m_gl_ID);

		glDeleteShader(vs);
		glDeleteShader(fs);

	}

	void Shader::Enable()
	{
		glUseProgram(m_gl_ID);
	}

	void Shader::Delete()
	{
		glDeleteProgram(m_gl_ID);
	}
	
	std::string Shader::ReadShaderFile(const char* _filename)
	{
		// Get the current working directory 
		std::filesystem::path currentPath = std::filesystem::current_path();

		// Construct a file path relative to the current working directory 
		std::filesystem::path file_path = currentPath / "ressources" / "Shaders" / _filename;

		std::cout << file_path << std::endl;
		std::ifstream in(file_path, std::ios::binary);

		if (in)
		{
			std::string contents;
			in.seekg(0, std::ios::end);
			contents.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&contents[0], contents.size());
			in.close();
			return(contents);
		}
		throw(errno);
	}
}