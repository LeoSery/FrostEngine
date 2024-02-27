#pragma once

#include "Core/Export.h"

#include <string>

namespace frost::core
{
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
