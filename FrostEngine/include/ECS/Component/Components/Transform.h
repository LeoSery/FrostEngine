#pragma once

/*!
* \file Transform.h
* 
* \brief Header file for the Transform class.
*/

#include "ECS/Component/IComponent.h"
#include "glm/vec2.hpp"

/*!
* \namespace frost::ECS
*
* \brief The namespace for FrostEngine's Entity Component System.
*/
namespace frost::ECS
{
	class GameObject;

	/*!
	* \class Transform
	* 
	* \brief The 'Transform' component is mandatory for every GameObject
	* in the scene, and defines the position, rotation and scale of the GameObject.
	* 
	* \details The 'Transform' is a component that is added by default when a GameObject
	* or any class inheriting it is created, and cannot be removed. It defines the
	* position, rotation and scale of the object to which it is attached.
	* It also has methods for translating, rotating or scaling the parent GameObject.
	*/
	class FROST_ENGINE_API Transform : public IComponent
	{
		/*!
		* \brief The RTTI definition for the Transform class.
		*
		* \def FROST_DEFINE_RTTI(Transform) This macro defines the RTTI for the Transform class.
		*/
		FROST_DEFINE_RTTI(Transform)

	public:

		// Constructors and Destructors
		Transform(GameObject& _GameObject);
		~Transform();

		// Frost engine life cycle methods
		virtual void Start() override;
		virtual void Update(float _DeltaTime) override;
		virtual void Destroy() override;

		// Getters and Setters
		void GetData(bool _ForceLoggerDraw) const;

		// Component methods
		void Translate(const glm::vec2& _Translation);
		void Rotate(float _Rotation);
		void Scale(const glm::vec2& _Scale);

		glm::vec2 GetForwardVector() const;

		// Fields
		glm::vec2 position = { 0, 0 };
		float rotation = 0;
		glm::vec2 scale = { 1, 1 };
		bool isMovingEntity = false;
	};
}