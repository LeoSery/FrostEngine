#include "Render/Buffer.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>

/*!
* \namespace frost::render
*
* \brief The namespace for FrostEngine's rendering functionalities.
*/
namespace frost::render
{
	struct Buffer::Internal
	{
		GLuint m_gl_ID;
	};

	Buffer::Buffer() : m_internal(new Internal)
	{

	}

	Buffer::~Buffer()
	{

	}

	unsigned int Buffer::CreateData(void* data, unsigned int size)
	{
		glCreateBuffers(1, &m_internal->m_gl_ID);
		glNamedBufferStorage(m_internal->m_gl_ID, size, data, 0);
		return this->GetBufferID();
	}

	unsigned int Buffer::GetBufferID()
	{
		return m_internal->m_gl_ID;
	}
}
