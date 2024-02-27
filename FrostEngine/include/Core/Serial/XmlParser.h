#pragma once

#include "Core/Export.h"

#include <rapidxml/rapidxml.hpp>

namespace frost::core
{
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
