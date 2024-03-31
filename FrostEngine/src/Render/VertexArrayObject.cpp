#include "Render/VertexArrayObject.h"
#include "Render/Texture.h"
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

	VertexArrayObject::VertexArrayObject()
		: Texture(nullptr)
	{
		m_positionLocation = { 0,0 };
		m_rotationLocation = 0.f;
		m_scaleLocation = { 1,1 };

		glCreateVertexArrays(1, &m_gl_ID); //Create VAO

		
		glEnableVertexArrayAttrib(m_gl_ID, 0); //Ennable attrib 0 of the VAO <-- uPosition in vertex shader
		glVertexArrayAttribBinding(m_gl_ID, 0, 0);
		glVertexArrayAttribFormat(m_gl_ID, 0, 2 /*attrib must have a size of two GL_Float*/, GL_FLOAT, GL_FALSE, 0);

		
		glEnableVertexArrayAttrib(m_gl_ID, 1);//Ennable attrib 1 of the VAO <-- uUV in vertex shader
		glVertexArrayAttribBinding(m_gl_ID, 1, 0); 
		glVertexArrayAttribFormat(m_gl_ID, 1, 2		/* attrib 1 have a size of 2 GL_FLOAT									*/
		, GL_FLOAT, GL_FALSE, 2 * sizeof(float));	/* and an offset of 2 * sizeof(float) from the beginning of the buffer	*/

	}

	VertexArrayObject::~VertexArrayObject()
	{
	}

	void VertexArrayObject::Bind()
	{
		glBindVertexArray(m_gl_ID);
		if (Texture != nullptr)
		{
			Texture->Bind();
		}
	}

	void VertexArrayObject::Unbind()
	{
		glBindVertexArray(0);

		if (Texture != nullptr)
		{
			Texture->Unbind();
		}

	}

	void VertexArrayObject::BindBuffer(E_TypeBuffer _bufferType, Buffer& _buffer)
	{
		switch (_bufferType)
		{
		case frost::render::VertexArrayObject::VBO:

			glVertexArrayVertexBuffer(m_gl_ID, 0, _buffer.GetBufferID(), 0 /*Offset par rapport au debut du buffer*/, 4 * sizeof(float) /*Data par vertice*/);

			break;
		case frost::render::VertexArrayObject::IBO:

			glVertexArrayElementBuffer(m_gl_ID, _buffer.GetBufferID());// This is to link vertices buffer[1] is the buffer that have order to draw triangle

			break;
		default:
			break;
		}

	}

	void VertexArrayObject::SetTexture(frost::render::Texture* _texture)
	{
		Texture = _texture;
	}

	Texture* VertexArrayObject::GetTexture()
	{
		return Texture;
	}


	void VertexArrayObject::SetLocation(glm::vec2 _newLocation)
	{
		m_positionLocation = _newLocation;
	}

	void VertexArrayObject::SetRotation(float _newRotation)
	{
		m_rotationLocation = _newRotation;
	}

	void VertexArrayObject::SetScale(glm::vec2 _newScale)
	{
		m_scaleLocation = _newScale;
	}

	glm::vec2 VertexArrayObject::GetLocation()
	{
		return m_positionLocation;
	}

	glm::vec2 VertexArrayObject::GetScale()
	{
		return m_scaleLocation;
	}

	float VertexArrayObject::GetRotation()
	{
		return m_rotationLocation;
	}
}
