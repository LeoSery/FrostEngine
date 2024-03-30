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
		/*
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
		virtual void Start() override;
		virtual void Update(float _DeltaTime) override;
		virtual void Destroy() override;

		// Getters and Setters
		[[nodiscard]] virtual void GetData(bool _ForceLoggerDraw) const;

		[[nodiscard]] std::string GetTexture() const;
		[[nodiscard]] void SetTexture(const std::string& _NewTexturePath);

		[[nodiscard]] glm::vec4 GetColor() const;
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
