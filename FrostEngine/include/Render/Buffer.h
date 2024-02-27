#pragma once

#include "Core/Export.h"

#include <memory>

namespace frost::core
{
	class FROST_ENGINE_API Buffer
	{

	public:

		// Constructor and Destructor
		explicit Buffer( void* data, unsigned int size);
		~Buffer();

		// Getters
		[[nodiscard]] unsigned int GetBufferID();
	private:
		struct Internal;
		std::unique_ptr<Internal> m_internal;
	};
}
