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

		/*!
		* \brief This method is called when the Transform is started.
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
		* \details Displays in the position, rotation and scale of the GameObject
		*
		* \fn GetData(bool _ForceLoggerDraw) const
		*
		* \param _ForceLoggerDraw indicates whether the info should be put
		* in the stack to be displayed at the next engine cycle,
		* or whether it should be displayed now.
		*/
		void GetData(bool _ForceLoggerDraw) const;

		// Component methods

		/*
		* \brief This method translates the GameObject by a given vector.
		* 
		* \fn Translate(const glm::vec2& _Translation)
		* 
		* \param _Translation the vector by which the GameObject should be translated.
		*/
		void Translate(const glm::vec2& _Translation);

		/*!
		* \brief This method rotates the GameObject by a given angle.
		* 
		* \fn Rotate(float _Rotation)
		* 
		* \param _Rotation the angle by which the GameObject should be rotated.
		*/
		void Rotate(float _Rotation);

		/*!
		* \brief This method scales the GameObject by a given vector.
		* 
		* \fn Scale(const glm::vec2& _Scale)
		* 
		* \param _Scale the vector by which the GameObject should be scaled.
		*/
		void Scale(const glm::vec2& _Scale);

		/*!
		* \brief This method returns the forward vector of the GameObject.
		* 
		* \fn GetForwardVector() const
		* 
		* \return the forward vector of the GameObject.
		*/
		glm::vec2 GetForwardVector() const;

		// Fields
		glm::vec2 position = { 0, 0 };
		float rotation = 0;
		glm::vec2 scale = { 1, 1 };
		bool isMovingEntity = false;
	};
}