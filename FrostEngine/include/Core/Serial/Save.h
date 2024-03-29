#pragma once

/*!
* \file Save.h
* 
* \brief Header file for the Save class.
*/

#include "Core/Export.h"

#include <string>

/*!
* \namespace frost::core
*
* \brief The namespace for the FrostEngine core functionalities.
*/
namespace frost::core
{
	/*!
	* \class Save
	* 
	* \brief The Save class is responsible for saving the game state.
	* 
	* \details The 'Save' class is used to save the game state, such as the position of the player.
	*/
	class FROST_ENGINE_API Save 
	{
		friend class XmlParser;

	protected:
		int m_protected_rotation = 0;
		int m_protected_lifePoint = 0;
		std::string m_protected_imagePath = "";

		struct Position
		{
			int x, y;
		};

		Position m_protected_pos{};
	};
}
