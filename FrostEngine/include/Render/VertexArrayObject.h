#pragma once

#include "Core/Export.h"
#include <glm/vec2.hpp>

namespace frost::core
{
	class Buffer;
	class Texture;

	class FROST_ENGINE_API VertexArrayObject
	{
	public:

		enum E_TypeBuffer
		{
			VBO,
			IBO
		};

		// Constructor and Destructor
		VertexArrayObject();
		~VertexArrayObject();

		// Methods
		void Bind();
		void Unbind();
		void BindBuffer(E_TypeBuffer _BufferType, Buffer& _Buffer);

		void SetTexture(Texture* _texture);
		Texture* GetTexture();

		// Getters and Setters
		[[nodiscard]] glm::vec2 GetLocation();
		[[nodiscard]] glm::vec2 GetScale();
		[[nodiscard]] float GetRotation();

		void SetLocation(glm::vec2 _NewLocation);
		void SetRotation(float _NewRotation);
		void SetScale(glm::vec2 _NewScale);

	private:
		unsigned int m_gl_ID;
		glm::vec2 m_positionLocation;
		float m_rotationLocation;
		glm::vec2 m_scaleLocation;

		Texture* Texture;
	};
}
