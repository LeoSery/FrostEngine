 #pragma once

/*!
* \file SpriteRenderer.h
* 
* \brief Header file for the SpriteRenderer class.
*/

#include "ECS/Component/IComponent.h"

#include "Render/VertexArrayObject.h"
#include "Render/Buffer.h"

#include "Core/Internal/Export.h"

#include "glm/vec4.hpp"

/*!
* \namespace frost::ECS
*
* \brief The namespace for FrostEngine's Entity Component System.
*/
namespace frost::ECS
{
	class GameObject;
	class Transform;
	class Texture;

	/*!
	* \enum S_SpriteType
	* 
	* \brief The enum for the different types of sprites.
	*/
	enum class S_SpriteType
	{
		none,
		square,
		triangle,
		circle
	};

	/*!
	* \class SpriteRenderer
	* 
	* \brief This class contains all the methods that make up the 'SpriteRenderer' component.
	* The 'SpriteRenderer' component is used to render an object on screen.
	* 
	* \details The 'SpriteRenderer' component sends information from the 'GameObject' to which
	* it is attached to the RenderDevice. It can be used to add a texture to an object or assign a color.
	*/
	class FROST_ENGINE_API SpriteRenderer : public IComponent
	{
		/*!
		* \brief The RTTI definition for the SpriteRenderer class.
		*
		* \def FROST_DEFINE_RTTI(SpriteRenderer) This macro defines the RTTI for the SpriteRenderer class.
		*/
		FROST_DEFINE_RTTI(SpriteRenderer)

	public:

		// Constructors and Destructors
		SpriteRenderer(GameObject& _GameObject);
		~SpriteRenderer();

		// Frost engine life cycle methods

		/*!
		* \brief This method is called when the SpriteRenderer is started.
		*
		* \details This method is inherited from the 'IComponent' class.
		* It is redefined in each component and allows you to apply a
		* different Start logic to each component.
		*
		* \fn vrirtual void Start() override
		*/
		virtual void Start() override;

		/*!
		* \brief This method is called by the engine at each cycle, and is used to update the component.
		*
		* \details This method is inherited from the 'IComponent' class.
		* It is redefined in each component and allows you to apply a
		* different Start logic to each component.
		*
		* \fn virtual void Update(float _DeltaTime) override
		*
		* \param _DeltaTime The time between the last frame and the current frame.
		*/
		virtual void Update(float _DeltaTime) override;

		// Getters and Setters

		/*
		* \brief This method logs the data linked to this component.
		*
		* \details Displays in the logger the path of the target texture and the color of the sprite.
		*
		* \fn GetData(bool _ForceLoggerDraw) const
		*
		* \param _ForceLoggerDraw indicates whether the info should be put
		* in the stack to be displayed at the next engine cycle,
		* or whether it should be displayed now.
		*/
		[[nodiscard]] virtual void GetData(bool _ForceLoggerDraw) const;

		/*
		* \brief This method return the path of the texture linked to the sprite.
		* 
		* \fn GetTexture() const
		* 
		* \return The path of the texture linked to the sprite.
		*/
		[[nodiscard]] std::string GetTexture() const;

		/*!
		* \brief This method sets the texture of the sprite.
		* 
		* \fn SetTexture(const std::string& _NewTexturePath)
		* 
		* \param _NewTexturePath The path of the new texture.
		*/
		[[nodiscard]] void SetTexture(const std::string& _NewTexturePath);

		/*!
		* \brief This method returns the color of the sprite.
		* 
		* \fn GetColor() const
		* 
		* \return A glm::vec4 containing the color of the sprite.
		*/
		[[nodiscard]] glm::vec4 GetColor() const;

		/*!
		* \brief This method sets the color of the sprite.
		* 
		* \fn SetColor(const glm::vec4& _NewColor)
		* 
		* \param _NewColor The new color of the sprite.
		*/
		void SetColor(const glm::vec4& _NewColor);

	private:

		std::string m_spriteTexturePath = "";
		glm::vec4 m_color = { 1, 1, 1, 1 };
		frost::render::Texture* m_spriteTexture;

		float* vertices;
		unsigned int* indices;

	public:

		// Render data
		frost::render::Buffer VBO;
		frost::render::Buffer IBO;
		frost::render::VertexArrayObject VAO;

	};
}
