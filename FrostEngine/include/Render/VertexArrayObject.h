#pragma once

/*!
* \file VertexArrayObject.h
* 
* \brief Header file for the VertexArrayObject class.
*/

#include "Core/Internal/Export.h"
#include <glm/vec2.hpp>

/*!
* \namespace frost::render
*
* The namespace for FrostEngine's rendering functionalities.
*/
namespace frost::render
{
	class Buffer;
	class Texture;

	/*!
	* \class VertexArrayObject
	* 
	* \brief The class that manages the VertexArrayObject of the FrostEngine.
	* 
	* details create, bind, unbind and set texture in a VertexArrayObject for the RenderDevice.
	*/
	class FROST_ENGINE_API VertexArrayObject
	{
	public:

		/*!
		* \enum E_TypeBuffer
		* 
		* \brief The enum that manages the type of buffer in the VertexArrayObject.
		*/
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
