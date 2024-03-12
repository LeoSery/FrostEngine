#pragma once

#include "Core/Export.h"

#include <memory>

namespace frost::core
{
	class FROST_ENGINE_API Buffer
	{

	public:

		// Constructor and Destructor
		explicit Buffer();
		~Buffer();

		unsigned int CreateData(void* data, unsigned int size);

		// Getters
		[[nodiscard]] unsigned int GetBufferID();
	private:
		struct Internal;
		std::unique_ptr<Internal> m_internal;
	};
}
