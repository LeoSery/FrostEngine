#pragma once

/*!
* \file BoxCollider.h
* 
* \brief Header file for the BoxCollider class.
*/

#include "Core/SceneManagement/SceneManager.h"
#include "Core/Internal/Export.h"

#include "ECS/Component/IComponent.h"

#include "glm/mat2x2.hpp"
#include <map>

/*!
* \namespace frost::ECS
*
* \brief The namespace for FrostEngine's Entity Component System.
*/
namespace frost::ECS
{
	class GameObject;
	class BoxCollider;

	/*!
	* \struct S_CollisionData
	* 
	* \brief A struct that holds data about a collision.
	* 
	* \details This structure contains collision data generated when
	* a 'Hit' is created as a result of a collision between two GameObjects.
	*/
	struct S_CollisionData
	{
		bool isColliding = false;
		BoxCollider* otherCollider = nullptr;
		float top = 0.0f;
		float bottom = 0.0f;
		float left = 0.0f;
		float right = 0.0f;
	};

	/*!
	* \enum E_CollisionResponse
	* 
	* \brief An enumeration that defines the possible responses to a collision.
	* 
	* \note Block : The GameObject will block the collision.
	* \note Ignore : The GameObject will ignore the collision.
	*/
	enum E_CollisionResponse
	{
		Block,
		Ignore
	};

	/*!
	* \enum E_CollisionChannel
	* 
	* \brief An enumeration that defines the possible collision channels.
	* 
	* \note Default : The default collision channel.
	* \note Player : The collision channel for the player.
	* \note Ennemy : The collision channel for the ennemies.
	* \note Projectile : The collision channel for the projectiles.
	*/
	enum E_CollisionChannel
	{
		Default = 0,
		Player = 1,
		Ennemy = 2,
		Projectile = 3,
	};

	/*!
	* \class BoxCollider
	* 
	* \brief This class contains all the methods that make up the 'BoxCollider' component.
	* The 'BoxCollider' component allows a GameObject to simulate collisions with other GameObjects
	* in the scene.
	* 
	* \details The 'BoxCollider' component is responsible for calculating the collisions
	* of the GameObject on which it is present. It has methods for calculating the bounds
	* of the object on which it is present, and it has methods for finding out whether the
	* object on which it is present collides with another GameObject that also has a 'BoxCollider'.
	*/
	class FROST_ENGINE_API BoxCollider : public IComponent
	{
		/*!
		* \brief The RTTI definition for the BoxCollider class.
		*
		* \def FROST_DEFINE_RTTI(BoxCollider) This macro defines the RTTI for the BoxCollider class.
		*/
		FROST_DEFINE_RTTI(BoxCollider)

	public:

		// Constructors and Destructors
		BoxCollider(GameObject& _GameObject);
		~BoxCollider();

		// Frost engine life cycle methods

		/*!
		* \brief This method is called when the BoxCollider is started.
		* 
		* \details This method is inherited from the 'IComponent' class.
		* It is redefined in each component and allows you to apply a
		* different Start logic to each component.
		* 
		* \fn virtual void Start() override
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

		// Methods

		/*!
		* \brief This method is used to check if the BoxCollider is colliding with another BoxCollider.
		*
		* \param _Other The BoxCollider with which to check for a collision.
		* 
		* \return A S_CollisionData struct containing the collision data.
		*/
		S_CollisionData IsColliding(BoxCollider& _Other);

		// Getters and Setters

		/*
		* \brief This method is used to get the 'IsStatic' property of the BoxCollider.
		* 
		* \fn GetIsStatic() const
		* 
		* \return A boolean value indicating whether the BoxCollider is static.
		*/
		[[nodiscard]] bool GetIsStatic() const;

		/*
		* \brief This method is used to set the 'IsStatic' property of the BoxCollider.
		* 
		* \fn SetIsStatic(bool _IsStatic)
		* 
		* \param _IsStatic A boolean value indicating whether the BoxCollider is static.
		*/
		void SetIsStatic(bool _IsStatic);

		/*
		* \brief This method logs the data linked to this component.
		* 
		* \details Displays in the logger whether the object is active and static.
		* 
		* \fn GetData(bool _ForceLoggerDraw) const
		* 
		* \param _ForceLoggerDraw indicates whether the info should be put
		* in the stack to be displayed at the next engine cycle,
		* or whether it should be displayed now.
		*/
		void GetData(bool _ForceLoggerDraw) const;

		/*
		* \brief This method returns the rotation matrix of the transform on which this GameObject is set.
		* 
		* \fn GetRotationMatrix() const
		* 
		* \return A glm::mat2 representing the rotation matrix of the transform.
		*/
		glm::mat2 GetRotationMatrix() const;

		/*
		* \brief This method returns the vertices of the BoxCollider
		* 
		* \details Return the current vertices based on the Transform component present on this GameObject.
		* 
		* \fn GetVertices() const
		* 
		* \return A std::vector<glm::vec2>* representing the vertices of the BoxCollider.
		*/
		std::vector<glm::vec2>* GetVertices() const;

		// Fields

		E_CollisionChannel m_collisionChannel;
		std::map<E_CollisionChannel, E_CollisionResponse> m_collisionSettings;
		std::vector<frost::ECS::GameObject*> CollidingObjects;

	private:
		// Methods
		S_CollisionData AABB(BoxCollider& _Other) const;

		// Settings
		bool m_isStatic = false;

		// Data
		std::vector<glm::vec2>* m_vertices = nullptr;

		// Components references
		frost::ECS::Transform* m_transform = nullptr;
		frost::core::Scene* m_currentScene = nullptr;
	};
}
