#pragma once

/*!
* \file Buffer.h
* 
* \brief Header file for the Buffer class.
*/

#include "Core/Internal/Export.h"

#include <memory>

/*!
* \namespace frost::render
*
* The namespace for FrostEngine's rendering functionalities.
*/
namespace frost::render
{
	/*!
	* \class Buffer
	* 
	* \brief allow to create a buffer.
	* 
	* \brief this class is used to create a buffer in the GPU.
	*/
	class FROST_ENGINE_API Buffer
	{

	public:

		// Constructor and Destructor
		explicit Buffer();
		~Buffer();

		// Methods
		unsigned int CreateData(void* data, unsigned int size);

		// Getters
		[[nodiscard]] unsigned int GetBufferID();

	private:

		struct Internal;
		std::unique_ptr<Internal> m_internal;
	};
}
