#pragma once
#include "Core/Export.h"
#include <rapidxml/rapidxml.hpp>
#include <filesystem>
#include <map>
#include <string>

namespace frost::core
{
	struct TextureData;

	class FROST_ENGINE_API TextureMgr
	{
	public:
		TextureMgr();
		~TextureMgr();
		bool LoadTexture(const std::filesystem::path& path);
		const TextureData& GetTextureData(const std::string& name) const;

#ifdef _DEBUG
		void DrawDebug() const;
#endif
	private:
		std::map<std::string, TextureData> Textures;
		//ToDo explicatino ssur l'erreur avec le const enlevé
		bool LoadTextureMetadata(std::filesystem::path& path, TextureData& textureData);
		bool LoadAnimationMetadata(rapidxml::xml_node<>* node, TextureData& textureData);
		//bool LoadStaticTileMetadata(rapidxml::xml_node<>* node, TextureData& textureData);
	};

	struct AnimationData
	{
		AnimationData();

		int StartX;
		int StartY;
		int SizeX;
		int SizeY;
		int OffsetX;
		int OffsetY;
		int AnimationSpriteCount;
		int SpriteOnLine;
		bool IsReverted;
		float TimeBetweenAnimationInS;
	};

	struct StaticTileData
	{
		int iStartX = 0;
		int iStartY = 0;
		int iSizeX = 0;
		int iSizeY = 0;
		bool bIsRevertedX = false;
		bool bIsRevertedY = false;

#ifdef _DEBUG
		void DrawDebug() const;
#endif
	};

	struct TextureData
	{
		TextureData();
		~TextureData();

		//To Do la variable texture à faire avec Mathieu OpenGl


		std::map<std::string, AnimationData> AnimationsData;
		std::map<std::string, StaticTileData> StaticTilesData;
	};
}

