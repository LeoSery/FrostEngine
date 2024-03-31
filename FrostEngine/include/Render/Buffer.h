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
	* \details this class is used to create a buffer in OpenGL context.
	* \n it store data in the GPU memory and save an adress to access it.
	*/
	class FROST_ENGINE_API Buffer
	{

	public:

		// Constructor / Destructor
		explicit Buffer();
		~Buffer();

		// Methods

		/*!
		* \brief Create a buffer.
		* \fn Create.
		* \_param data the data to store in the buffer.
		* \_param size the size of the data.
		* \return the id of the buffer.
		*/
		unsigned int CreateData(void* data, unsigned int size);

		/*!
		* \brief Get The Buffer ID.
		*/
		unsigned int GetBufferID();

	private:

		struct Internal;
		std::unique_ptr<Internal> m_internal;
	};
}
