#pragma once

#include "Core/Export.h"
#include <rapidxml/rapidxml.hpp>

namespace frost::core
{
	class FROST_ENGINE_API XmlParser
	{
	public:
		XmlParser() = default;
		bool Parse(const char* filePath);
		void SetParser();
	private:

		bool ParsePlayerNode(rapidxml::xml_node<>* xmlNode);
		bool ParseRootNode(rapidxml::xml_document<>& xmlDoc);

	};
}


