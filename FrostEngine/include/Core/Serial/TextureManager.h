#pragma once

/*!
* \file TextureManager.h
* 
* \brief Header file for the TextureManager class.
*/

#include "Core/Export.h"

#include <rapidxml/rapidxml.hpp>
#include <filesystem>
#include <string>
#include <map>

/*!
* \namespace frost::core
*
* \brief The namespace for the FrostEngine core functionalities.
*/
namespace frost::core
{
	struct S_TextureData;

	/*!
	* \class TextureManager
	* 
	* \brief This class is used to manage textures.
	* 
	* \details This class is used to load textures and store their metadata.
	*/
	class FROST_ENGINE_API TextureManager
	{
	public:

		// Constructor and Destructor
		TextureManager();
		~TextureManager();

		// Methods
		bool LoadTexture(const std::filesystem::path& path);

		// Getters
		[[nodiscard]] const S_TextureData& GetTextureData(const std::string& name) const;

		#ifdef _DEBUG
		void DrawDebug() const;
		#endif

	private:
		bool LoadTextureMetadata(std::filesystem::path& path, S_TextureData& textureData);
		bool LoadAnimationMetadata(rapidxml::xml_node<>* node, S_TextureData& textureData);

		std::map<std::string, S_TextureData> m_textures;
	};

	/*
	* \struct S_AnimationData
	* 
	* \brief This struct is used to store the metadata of an animation.
	*/
	struct S_AnimationData
	{
		// Struct fields
		int startX;
		int startY;
		int sizeX;
		int sizeY;
		int offsetX;
		int offsetY;
		int animationSpriteCount;
		int spriteOnLine;
		bool isReverted;
		float timeBetweenAnimationInS;

		// Struct methods
		S_AnimationData();
	};

	/*
	* \struct S_StaticTileData
	* 
	* \brief This struct is used to store the metadata of a static tile.
	*/
	struct S_StaticTileData
	{
		// Struct fields
		int iStartX = 0;
		int iStartY = 0;
		int iSizeX = 0;
		int iSizeY = 0;
		bool bIsRevertedX = false;
		bool bIsRevertedY = false;

		// Struct methods
		#ifdef _DEBUG
		void DrawDebug() const;
		#endif
	};

	/*
	* \struct S_TextureData
	* 
	* \brief This struct is used to store the metadata of a texture.
	*/
	struct S_TextureData
	{
		// Struct Constructor and Destructor
		S_TextureData();
		~S_TextureData();

		std::map<std::string, S_AnimationData> animationsData;
		std::map<std::string, S_StaticTileData> staticTilesData;
	};
}
