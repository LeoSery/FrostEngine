#pragma once
#include "Core/Export.h"
#include <glm/vec2.hpp>
namespace frost::core 
{


	class FROST_ENGINE_API VertexArrayObject
	{
	private: 
		unsigned int m_gl_ID;
	
		glm::vec2 positionLocation;
		float rotationLocation;
		glm::vec2 scaleLocation;
	
	public:
	
		enum eShape
		{
			Square
		};
	
		
		
		VertexArrayObject(unsigned int buffers[2]);
		VertexArrayObject(const void* vertices, unsigned int indices[]);
		~VertexArrayObject();
	
	
		void Bind();
		void Unbind();
	
		void SetLocation(glm::vec2 _newLocation);
		void SetRotation(float _newRotation);
		void SetScale(glm::vec2 _newScale);
		
		glm::vec2 GetLocation();
		glm::vec2 GetScale();
		float GetRotation();
		
	
	};

}