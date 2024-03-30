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
	* \brief The class that manages the Texture of the FrostEngine.
	* 
	* details create, bind, undbing Textres and Images on the GPU.
	*/
	class FROST_ENGINE_API Texture
	{
	public:

		// Constructor and Destructor
		Texture(const std::string& _Name);
		Texture();
		~Texture();

		// Fields
		bool SetTexture(const std::string _name);

		// Methods
		void Bind(unsigned int _Slot = 0) const;
		void Unbind();

		// Getters
		[[nodiscard]] inline int GetWidth() const { return Width; }
		[[nodiscard]] inline int GetHeight() const { return Height; }
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
