#include "Render/Texture.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <filesystem>
#include <fstream>
#include "Utils/stb_image.h"
#include <iostream>

namespace frost::core 
{
	Texture::Texture(const std::string& _name)
		: m_ID(0), m_FilePath(_name), m_LocalBuffer(NULL), m_Width(0), m_Height(0), m_BPP(0)
	{
		glGenTextures(1, &m_ID);
		glBindTexture(GL_TEXTURE_2D, m_ID);
	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		stbi_set_flip_vertically_on_load(1);
	
		LoadImage(_name);
	
		if (!m_LocalBuffer)
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		else
		{
			//utils::Logger::GetInstance()->LogInfo("Loaded Texture : " + _name);
			//utils::Logger::GetInstance()->Show();
			//this is probably not the correct way to do it but i need it done
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
			if (m_LocalBuffer)
			{
				stbi_image_free(m_LocalBuffer);
			}
		}
	
		
	}
	
	frost::core::Texture::~Texture()
	{
	
	}
	
	void frost::core::Texture::Bind(unsigned int slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_ID);
	}
	
	void frost::core::Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
	
	bool frost::core::Texture::LoadImage(const std::string _name)
	{
	
		std::filesystem::path file_path = _name;
		std::ifstream f(_name);
		if (!f.good())
		{
			// Construct a file path relative to the current working directory 
			file_path = std::filesystem::current_path() / "ressources" / "Textures" / _name;
	
			f.open(file_path);
			if (!f.good())
			{
				//FROST_ERROR
				return false;
			}
	
		}
		
		m_LocalBuffer = stbi_load(file_path.string().c_str(), &m_Width, &m_Height, &m_BPP, 4);
		return true;
	}
}