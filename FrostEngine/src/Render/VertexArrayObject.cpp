#include "Render/VertexArrayObject.h"
#include "Render/Buffer.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

namespace frost::core 
{
	
	VertexArrayObject::VertexArrayObject()
	{
		m_positionLocation = { 0,0 };
		m_rotationLocation = 0.f;
		m_scaleLocation = {1,1};
		
		glCreateVertexArrays(1, &m_gl_ID);
	
		//On active l'attribut 0 du VAO
		glEnableVertexArrayAttrib(m_gl_ID, 0);
		glVertexArrayAttribBinding(m_gl_ID, 0, 0);
		glVertexArrayAttribFormat(m_gl_ID, 0, 2 /*L'attribut a une taille de 2 GL_FLOAT*/, GL_FLOAT, GL_FALSE, 0);
	
		//On active l'attribut 1 du VAO <-- TexCoord
		glEnableVertexArrayAttrib(m_gl_ID, 1);
		glVertexArrayAttribBinding(m_gl_ID, 1, 0); //On Bind l'attribut 1 qui est la couleur des vertices
		glVertexArrayAttribFormat(m_gl_ID, 1, 2 /*L'attribut a une taille de 3 GL_FLOAT*/, GL_FLOAT, GL_FALSE, 2 * sizeof(float)); // et un offset de 2 * la taille d'un float

	}

	VertexArrayObject::~VertexArrayObject()
	{
	}
	
	void VertexArrayObject::Bind()
	{
		glBindVertexArray(m_gl_ID);
	}
	
	void VertexArrayObject::Unbind()
	{
		glBindVertexArray(0);
	}

	void VertexArrayObject::BindBuffer( E_TypeBuffer _bufferType, Buffer& _buffer)
	{
		switch (_bufferType)
		{
		case frost::core::VertexArrayObject::VBO:
			//la on bind ? 
			glVertexArrayVertexBuffer(m_gl_ID, 0, _buffer.GetBufferID(), 0 /*Offset par rapport au debut du buffer*/, 4 * sizeof(float) /*Data par vertice*/);

			break;
		case frost::core::VertexArrayObject::IBO:
			//la on bind aussi ?
			glVertexArrayElementBuffer(m_gl_ID, _buffer.GetBufferID());// This is to link vertices buffer[1] is the buffer that have order to draw triangle

			break;
		default:
			break;
		}
		
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