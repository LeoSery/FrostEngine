#pragma once

/*!
* \file XmlParser.h
* 
* \brief Header file for the XmlParser class.
*/

#include "Core/Export.h"

#include <rapidxml/rapidxml.hpp>

/*!
* \namespace frost::core
*
* \brief The namespace for the FrostEngine core functionalities.
*/
namespace frost::core
{
	/*!
	* \class XmlParser
	* 
	* \brief Class for parsing XML files.
	* 
	* \details This class is used to parse XML files and extract data from them.
	*/
	class FROST_ENGINE_API XmlParser
	{
	public:

		// Constructor
		XmlParser() = default;

		// Setters
		void SetParser();

		// Methods
		bool Parse(const char* _FilePath);

	private:
		bool ParsePlayerNode(rapidxml::xml_node<>* _XmlNode);
		bool ParseRootNode(rapidxml::xml_document<>& _XmlDoc);
	};
}
