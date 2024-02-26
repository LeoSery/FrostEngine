#include "Render/Buffer.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>

namespace frost::core
{

	struct Buffer::Internal
	{
		GLuint m_gl_ID;
	};

	Buffer::Buffer( void* data , unsigned int size)
		:m_internal(new Internal)
	{
		glCreateBuffers(1, &m_internal->m_gl_ID);
		glNamedBufferStorage(m_internal->m_gl_ID, size , data, 0);

	}

	Buffer::~Buffer()
	{
	}

	unsigned int Buffer::GetBufferID()
	{
		return m_internal->m_gl_ID;
	}
}
