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

		/*!\brief Bind the VertexArrayObject and the texture if set.
		* \details when the VertexArrayObject is binded, OpenGL will use it to render the object with the vaos attributes.
		* \note The VertexArrayObject must be binded before rendering the object.
		*/
		void Bind();

		/*!\brief Unbind the VertexArrayObject.
		* \note The VertexArrayObject must be unbinded after rendering the object.
		*/
		void Unbind();

		/*!\brief Bind a buffer to the VertexArrayObject.
		* \param _BufferType The type of buffer to bind.
		* \param _Buffer The buffer to bind.
		*/
		void BindBuffer(E_TypeBuffer _BufferType, Buffer& _Buffer);

		/*!\brief Set the texture of the VertexArrayObject.
		* \param _texture The Texture Object to set.
		*/
		void SetTexture(Texture* _texture);
		
		/*!\brief Get the texture of the VertexArrayObject.*/
		Texture* GetTexture();

		// Getters and Setters
		[[nodiscard]] glm::vec2 GetLocation();
		[[nodiscard]] glm::vec2 GetScale();
		[[nodiscard]] float GetRotation();

		// Setters

		/*! \brief Set the location of the VertexArrayObject.
		* \param _NewLocation The new location of the VertexArrayObject.
		* \details The location is the position of the object in the shader.
		*/
		void SetLocation(glm::vec2 _NewLocation);

		/*! \brief Set the rotation of the VertexArrayObject.
		* \param _NewRotation The new rotation of the VertexArrayObject.
		* \details The rotation is the rotation of the object in the shader.
		*/
		void SetRotation(float _NewRotation);
		
		/*! \brief Set the scale of the VertexArrayObject.
		* \param _NewScale The new scale of the VertexArrayObject.
		* \details The scale is the scale of the object in the shader.
		*/
		void SetScale(glm::vec2 _NewScale);

	private:
		unsigned int m_gl_ID;
		glm::vec2 m_positionLocation;
		float m_rotationLocation;
		glm::vec2 m_scaleLocation;

		Texture* Texture;
	};
}
