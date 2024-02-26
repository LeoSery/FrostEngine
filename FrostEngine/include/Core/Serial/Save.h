#pragma once

#include "Core/Export.h"
#include <string>

namespace frost::core
{
	class FROST_ENGINE_API Save 
	{
	friend class XmlParser;
	public:

	protected:


		int Rotation = 0;
		int LifePoint = 0;
		std::string ImagePath = "";
		struct Position
		{
			int x, y;
		};
		Position Pos{};
	};

}

