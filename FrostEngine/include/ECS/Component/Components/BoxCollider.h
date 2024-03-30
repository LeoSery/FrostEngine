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
		virtual void Start() override;
		virtual void Update(float _DeltaTime) override;
		virtual void Destroy() override;

		// Methods
		S_CollisionData IsColliding(BoxCollider& _Other);

		// Getters and Setters
		[[nodiscard]] bool GetIsStatic() const;
		void SetIsStatic(bool _IsStatic);
		void GetData(bool _ForceLoggerDraw) const;
		glm::mat2 GetRotationMatrix() const;
		std::vector<glm::vec2>* GetVertices() const;

		// Fields
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
