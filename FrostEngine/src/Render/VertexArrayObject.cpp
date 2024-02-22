#include "Render/VertexArrayObject.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

float vertices[] = {
			-0.5f,  0.5f, /*Color*/0.5f, 0.0f, 0.0f,
			-0.5f, -0.5f, /*Color*/0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, /*Color*/0.5f, 1.0f, 0.0f,
			 0.5f,  0.5f, /*Color*/1.0f, 0.8f, 1.0f
};

unsigned int indices[] = { 0, 1, 2, 0, 2, 3 };

VertexArrayObject::VertexArrayObject(unsigned int buffers[2])
{
	
	glCreateVertexArrays(1, &m_gl_ID);
	glVertexArrayVertexBuffer(m_gl_ID, 0, buffers[0]
		, 0 /*Offset par rapport au debut du buffer*/
		, 5 * sizeof(float) /*Data par vertice*/);

	//On active l'attribut 0 du VAO
	glEnableVertexArrayAttrib(m_gl_ID, 0);
	glVertexArrayAttribBinding(m_gl_ID, 0, 0);
	glVertexArrayAttribFormat(m_gl_ID, 0, 2 /*L'attribut a une taille de deux GL_FLOAT*/, GL_FLOAT, GL_FALSE, 0);

	//On active l'attribut 1 du VAO
	glEnableVertexArrayAttrib(m_gl_ID, 1);
	glVertexArrayAttribBinding(m_gl_ID, 1, 0); //On Bind l'attribut 1 au buffer 0 qu'on lui a passer au dessus

	glVertexArrayAttribFormat(m_gl_ID, 1, 3 /*L'attribut a une taille de deux GL_FLOAT*/, GL_FLOAT, GL_FALSE, 2 * sizeof(float)); // et un offset de 2
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
}
