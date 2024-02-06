#pragma once

#include "Core/Export.h"

#include <glm/vec2.hpp>
#include <string_view>

namespace frost
{
	class FROST_ENGINE_API Window
	{
		explicit Window(std::string_view name, const glm::vec2& size);
		~Window() = default;
	};
}
