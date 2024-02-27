#include "Core/Serial/TextureManager.h"

#include <rapidxml/rapidxml_utils.hpp>
#include <Utils/Logger.h>


frost::core::TextureManager::TextureManager()
{
}

frost::core::TextureManager::~TextureManager()
{
	m_textures.clear();
}

bool frost::core::TextureManager::LoadTexture(const std::filesystem::path& path)
{
	if (!std::filesystem::exists(path.native()))
	{
		std::string message = "Texture file doesn't exist ";
		message += path.string();

		utils::Logger::LogError(message);

		return false;
	}

	std::filesystem::path metadataPath = path;
	metadataPath = metadataPath.replace_extension(".xml");
	if (!std::filesystem::exists(metadataPath.native()))
	{
		std::string message = "Texture metadata file doesn't exist ";
		message += metadataPath.string();
		utils::Logger::LogError(message);
		return false;
	}


	auto p = m_textures.emplace(path.string(), S_TextureData());
	if (!p.second)
	{
		std::string message = "LoadTexture: Internal error. Cannot emplace in map";
		utils::Logger::LogError(message);
		return false;
	}

	S_TextureData& textureData = p.first->second;
	if (!LoadTextureMetadata(metadataPath, textureData))
	{
		std::string message = "Something went wrong while parsing metadata file ";
		message += metadataPath.string();
		utils::Logger::LogError(message);
		return false;
	}

	//ToDo Texture OpenGL Mathieu
	/*if (!textureData.Texture.loadFromFile(path.string()))
	{
		std::string message = "Something went wrong while loading texture ";
		message += path.string();
		return false;
	}*/

	return true;
}

bool frost::core::TextureManager::LoadTextureMetadata(std::filesystem::path& path, S_TextureData& textureData)
{
	rapidxml::file<> metadataFile(path.string().c_str());
	if (metadataFile.size() == 0)
	{
		std::string message = "LoadTextureMetadata: Cannot open file ";
		message += path.string();
		return false;
	}

	rapidxml::xml_document metadataXml;
	metadataXml.parse<0>(metadataFile.data());

	if (rapidxml::xml_node<>* node = metadataXml.first_node("Animations"))
	{
		if (!LoadAnimationMetadata(node, textureData))
		{
			std::string message = "Something went wrong while parsing Animation metadata file ";
			message += path.string();
			utils::Logger::LogError(message);
			return false;
		}
	}

	if (rapidxml::xml_node<>* node = metadataXml.first_node("Backgrounds"))
	{
		/*if (!LoadStaticTileMetadata(node, textureData))
		{
			std::string message = "Something went wrong while parsing StaticTile metadata file ";
			message += path.string();
			utils::Logger::LogError(message);
			return false;
		}*/
	}
	return true;
}

bool frost::core::TextureManager::LoadAnimationMetadata(rapidxml::xml_node<>* node, S_TextureData& textureData)
{
	if (!node)
	{
		return false;
	}

	rapidxml::xml_node<>* animationNode = node->first_node();
	while (animationNode)
	{
		rapidxml::xml_attribute<>* nameAttribute = animationNode->first_attribute("Name");
		if (nameAttribute)
		{
			auto p = textureData.animationsData.emplace(std::string(nameAttribute->value(), nameAttribute->value_size()), S_AnimationData());
			if (p.second)
			{
				S_AnimationData& data = p.first->second;
				if (rapidxml::xml_node<>* innerNode = animationNode->first_node("X"))
				{
					std::string value(innerNode->value(), innerNode->value_size());
					data.startX = atoi(value.c_str());
				}

				if (rapidxml::xml_node<>* innerNode = animationNode->first_node("Y"))
				{
					std::string value(innerNode->value(), innerNode->value_size());
					data.startY = atoi(value.c_str());
				}

				if (rapidxml::xml_node<>* innerNode = animationNode->first_node("SizeX"))
				{
					std::string value(innerNode->value(), innerNode->value_size());
					data.sizeX = atoi(value.c_str());
				}

				if (rapidxml::xml_node<>* innerNode = animationNode->first_node("SizeY"))
				{
					std::string value(innerNode->value(), innerNode->value_size());
					data.sizeY = atoi(value.c_str());
				}

				if (rapidxml::xml_node<>* innerNode = animationNode->first_node("OffsetX"))
				{
					std::string value(innerNode->value(), innerNode->value_size());
					data.offsetX = atoi(value.c_str());
				}

				if (rapidxml::xml_node<>* innerNode = animationNode->first_node("OffsetY"))
				{
					std::string value(innerNode->value(), innerNode->value_size());
					data.offsetY = atoi(value.c_str());
				}

				if (rapidxml::xml_node<>* innerNode = animationNode->first_node("SpriteNum"))
				{
					std::string value(innerNode->value(), innerNode->value_size());
					data.animationSpriteCount = atoi(value.c_str());
				}

				if (rapidxml::xml_node<>* innerNode = animationNode->first_node("SpritesOnLine"))
				{
					std::string value(innerNode->value(), innerNode->value_size());
					data.spriteOnLine = atoi(value.c_str());
				}

				if (rapidxml::xml_node<>* innerNode = animationNode->first_node("Reverted"))
				{
					std::string value(innerNode->value(), innerNode->value_size());
					data.isReverted = atoi(value.c_str());
				}

				if (rapidxml::xml_node<>* innerNode = animationNode->first_node("TimeBetweenAnimation"))
				{
					std::string value(innerNode->value(), innerNode->value_size());
					data.timeBetweenAnimationInS = std::stof(value.c_str());
				}
			}
			else
			{
				std::string message = "LoadAnimationMetadata: Cannot add animation ";
				message += nameAttribute->value();
				message += ". Ignore it";
				utils::Logger::LogWarning(message);
			}
		}
		else
		{
			utils::Logger::LogWarning("LoadAnimationMetadata: Find a animation node with no name. Ignore it");
		}

		animationNode = animationNode->next_sibling();
	}

	return true;
}

/*bool frost::core::TextureMgr::LoadStaticTileMetadata(rapidxml::xml_node<>* node, TextureData& textureData)
{
	return false;
}*/

frost::core::S_AnimationData::S_AnimationData()
{
}

frost::core::S_TextureData::S_TextureData()
{
}

frost::core::S_TextureData::~S_TextureData()
{
}
