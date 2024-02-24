#pragma once
#include "Core/Export.h"
#include <glm/vec2.hpp>
namespace frost::core 
{

	class Buffer;

	class FROST_ENGINE_API VertexArrayObject
	{
	private: 
		unsigned int m_gl_ID;
	
		glm::vec2 positionLocation;
		float rotationLocation;
		glm::vec2 scaleLocation;

	
	public:
	
		enum eTypeBuffer
		{
			VBO,
			IBO
		};

		
		VertexArrayObject();

		~VertexArrayObject();
	
	
		void Bind();
		void Unbind();

		void BindBuffer(eTypeBuffer _bufferType,Buffer& _buffer);
		

		void SetLocation(glm::vec2 _newLocation);
		void SetRotation(float _newRotation);
		void SetScale(glm::vec2 _newScale);
		
		glm::vec2 GetLocation();
		glm::vec2 GetScale();
		float GetRotation();
		
	
	};

}