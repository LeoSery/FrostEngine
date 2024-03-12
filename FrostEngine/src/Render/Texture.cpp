#include "Utils/stb_image.h"
#include "Render/Texture.h"
#include "Utils/Logger.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <filesystem>
#include <iostream>
#include <fstream>

namespace frost::core
{
	Texture::Texture(const std::string& _name)
		: ID(0), FilePath(_name), LocalBuffer(NULL), Width(0), Height(0), BPP(0)
	{
		initialize();
		SetTexture(_name);


	}

	Texture::Texture()
	{

		initialize();
		SetTexture("T_Debug.png");

	}

	frost::core::Texture::~Texture()
	{

	}

	void Texture::initialize()
	{
		glGenTextures(1, &ID);
		glBindTexture(GL_TEXTURE_2D, ID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		stbi_set_flip_vertically_on_load(1);
	}

	bool Texture::SetTexture(const std::string _name)
	{

		if (!LoadImage(_name))
		{
			frost::utils::Logger::LogError("Failed to load texture : " + _name);
			frost::utils::Logger::GetInstance()->Show();
			return false;
		}
		else
		{
			//utils::Logger::GetInstance()->LogInfo("Loaded Texture : " + _name);
			//this is probably not the correct way to do it but i need it done
			glBindTexture(GL_TEXTURE_2D, ID);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, LocalBuffer);
			if (LocalBuffer)
			{
				stbi_image_free(LocalBuffer);
			}
			return true;
		}
	}

	void frost::core::Texture::Bind(unsigned int slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, ID);

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

		LocalBuffer = stbi_load(file_path.string().c_str(), &Width, &Height, &BPP, 4);
		return true;
	}




}