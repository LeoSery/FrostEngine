#pragma once

/*!
* \file Texture.h
* 
* \brief Header file for the Texture class.
*/

#include "Core/Internal/Export.h"

#include <string>

/*!
* \namespace frost::render
*
* The namespace for FrostEngine's rendering functionalities.
*/
namespace frost::render
{
	/*!
	* \class Texture
	* 
	* \brief A class that represents a Texture.
	* \details Texture can load images and bind them.
	* \n when a VAO is bind it bind the Texture automatically to render the geometry.
	* 
	* \details this class is used in SpriteRenderer.
	*/
	class FROST_ENGINE_API Texture
	{
	public:

		/*!
		* \brief Constructor for the Texture class.
		* 
		*\param _Name the path of the texture. 
		
		*/
		Texture(const std::string& _Name);
		Texture();
		~Texture();

		/*!
		* \brief Set the texture to the given path.
		*/
		bool SetTexture(const std::string _name);

		/*!
		* \brief Bind the texture in openGL.
		*/
		void Bind(unsigned int _Slot = 0) const;

		/*!
		* \brief Unbind the texture in openGL.
		*/
		void Unbind();

		/*! 
		*\brief Get the width of the texture.*/
		[[nodiscard]] inline int GetWidth() const { return Width; }
		/*!
		* \brief Get the height of the texture.*/
		[[nodiscard]] inline int GetHeight() const { return Height; }
		/*!
		* \brief Get the ID of the texture.*/
		[[nodiscard]] inline int GetBPP() const { return BPP; }
		[[nodiscard]] inline unsigned int GetID() const { return ID; }


	private:
		void initialize();
		bool LoadImage(const std::string _name);

		unsigned int ID;
		std::string FilePath;
		unsigned char* LocalBuffer;
		int Width, Height, BPP;
	};
}
