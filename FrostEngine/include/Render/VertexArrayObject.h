#pragma once
class VertexArrayObject
{
private: 
	unsigned int m_gl_ID;

public:
	VertexArrayObject(unsigned int buffers[2]);
	~VertexArrayObject();

	void Bind();
	void Unbind();
	
};

