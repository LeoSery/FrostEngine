#pragma once
#include "Core/Export.h"
#include <memory>

namespace frost::core
{
	class FROST_ENGINE_API Buffer
	{
	private:

		struct Internal;
		std::unique_ptr<Internal> m_internal;

	public:

		explicit Buffer( void* data, unsigned int size);
		~Buffer();

		unsigned int GetBufferID();
	};

}


