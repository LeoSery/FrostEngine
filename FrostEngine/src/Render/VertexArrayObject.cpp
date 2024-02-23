#include "Render/VertexArrayObject.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

namespace frost::core 
{
	
	VertexArrayObject::VertexArrayObject(unsigned int buffers[2])
	{
		positionLocation = { 0,0 };
		rotationLocation = 0.f;
		scaleLocation = {1,1};
		
		glCreateVertexArrays(1, &m_gl_ID);
	
		/*On lui decrit comment lire la data*/
		glVertexArrayVertexBuffer(m_gl_ID, 0, buffers[0], 0 /*Offset par rapport au debut du buffer*/, 5 * sizeof(float) /*Data par vertice*/);
	
		//On active l'attribut 0 du VAO
		glEnableVertexArrayAttrib(m_gl_ID, 0);
		glVertexArrayAttribBinding(m_gl_ID, 0, 0);
		glVertexArrayAttribFormat(m_gl_ID, 0, 2 /*L'attribut a une taille de 2 GL_FLOAT*/, GL_FLOAT, GL_FALSE, 0);
	
		//On active l'attribut 1 du VAO
		glEnableVertexArrayAttrib(m_gl_ID, 1);
		glVertexArrayAttribBinding(m_gl_ID, 1, 0); //On Bind l'attribut 1 qui est la couleur des vertices
		glVertexArrayAttribFormat(m_gl_ID, 1, 3 /*L'attribut a une taille de 3 GL_FLOAT*/, GL_FLOAT, GL_FALSE, 2 * sizeof(float)); // et un offset de 2
	
		//Vertex Shader
		glVertexArrayElementBuffer(m_gl_ID, buffers[1]);// This is to link vertices buffer[1] is the buffer that have order to draw triangle
	
	
	
	}


	VertexArrayObject::VertexArrayObject(const void* vertices, unsigned int indices[])
	{
		positionLocation = { 0,0 };
		rotationLocation = 0.f;
		scaleLocation = { 1,1 };
	
		unsigned int buffers[2];
		glCreateBuffers(2, buffers); //Hey open gl i need 2 IDS to store things
		glNamedBufferStorage(buffers[0], sizeof(vertices), vertices, 0); //Buffer 0 = VBO
		glNamedBufferStorage(buffers[1], sizeof(indices), indices, 0);
		
		
		glCreateVertexArrays(1, &m_gl_ID);

		/*On lui decrit comment lire la data*/
		glVertexArrayVertexBuffer(m_gl_ID, 0, buffers[0], 0 /*Offset par rapport au debut du buffer*/, 5 * sizeof(float) /*Data par vertice*/);

		//On active l'attribut 0 du VAO
		glEnableVertexArrayAttrib(m_gl_ID, 0);
		glVertexArrayAttribBinding(m_gl_ID, 0, 0);
		glVertexArrayAttribFormat(m_gl_ID, 0, 2 /*L'attribut a une taille de 2 GL_FLOAT*/, GL_FLOAT, GL_FALSE, 0);

		//On active l'attribut 1 du VAO
		glEnableVertexArrayAttrib(m_gl_ID, 1);
		glVertexArrayAttribBinding(m_gl_ID, 1, 0); //On Bind l'attribut 1 qui est la couleur des vertices
		glVertexArrayAttribFormat(m_gl_ID, 1, 3 /*L'attribut a une taille de 3 GL_FLOAT*/, GL_FLOAT, GL_FALSE, 2 * sizeof(float)); // et un offset de 2

		//Vertex Shader
		glVertexArrayElementBuffer(m_gl_ID, buffers[1]);// This is to link vertices buffer[1] is the buffer that have order to draw triangle
	
	
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
	
	void VertexArrayObject::SetLocation(glm::vec2 _newLocation)
	{
		positionLocation = _newLocation;
	}
	
	void VertexArrayObject::SetRotation(float _newRotation)
	{
		rotationLocation = _newRotation;
	}
	
	void VertexArrayObject::SetScale(glm::vec2 _newScale)
	{
		scaleLocation = _newScale;
	}
	
	glm::vec2 VertexArrayObject::GetLocation()
	{
		return positionLocation;
	}
	
	glm::vec2 VertexArrayObject::GetScale()
	{
		return scaleLocation;
	}
	
	float VertexArrayObject::GetRotation()
	{
		return rotationLocation;
	}
	
	
}