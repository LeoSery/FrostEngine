#pragma once

/*!
* \file GameObject.h
* 
* \brief Header file for the GameObject class.
*/

#include "ECS/Component/Components/Transform.h"
#include "Core/Internal/AuthorizationBadge.h"
#include "ECS/System/Tree.h"

#include "Core/Internal/Export.h"

#define UUID_SYSTEM_GENERATOR
#include "stduuid/uuid.h"

#include <unordered_set>
#include <string>

namespace frost::core
{
	class SceneManager;
}
/*!
* \namespace frost::ECS
*
* \brief The namespace for FrostEngine's Entity Component System.
*/
namespace frost::ECS
{
	class IComponent;
	struct S_CollisionData;

	/*!
	* \class GameObject
	* 
	* \brief The 'GameObject' class is the basic class for any object present
	* in the scenes that constitute a game.
	*/
	class FROST_ENGINE_API GameObject : public Tree<GameObject>
	{
	protected:
		// Constructors and Destructors
		explicit GameObject(std::string _Name, GameObject* _Parent = nullptr);
		void Init();

	public:

		/*!
		* \brief Custom constructor for the 'GameObject' class.
		* 
		* \details This constructor can be called by classes that inherit from GameObject,
		* so that they can call cycle methods that are virtual.
		* 
		* \fn GameObject::New(std::string _Name, GameObject* _Parent)
		* 
		* \param _Name The name of the GameObject.
		* \param _Parent The parent of the GameObject.
		* 
		* \return GameObject* The GameObject created.
		*/
		static GameObject* New(std::string _Name, GameObject* _Parent);

		/*!
		* \brief Custom constructor for the 'GameObject' class.
		* 
		* \details Delete all the components of the GameObject and delete the GameObject itself.
		* 
		* \fn GameObject::~GameObject()
		*/
		~GameObject();

		// Frost engine life cycle methods

		/*!
		* \brief This is the method that will be executed when the GameObject is created.
		*
		* \details This method is purely virtual and must be implemented class that inherits from GameObject.
		*
		* \fn virutal void Start() = 0;
		*/
		virtual void Start();

		/*!
		* \brief This is the method that will be executed every frame.
		* 
		* \details This method is purely virtual and must be implemented class that inherits from GameObject.
		* 
		* \fn virutal void Update(float _DeltaTime) = 0;
		* 
		* \param _DeltaTime The time that has passed since the last frame.
		*/
		void Update(float _DeltaTime);

		/*!
		* \brief This method place the GameObject in the destroy queue.
		* 
		* \details For a GameObject to be destroyed, it must be placed
		* in the destruction queue to be deleted at the next engine cycle.
		* 
		* fn virtual void Destroy();
		*/
		virtual void Destroy();

		// Getters and Setters

		/*!
		* \brief Get the name of the GameObject.
		* 
		* \details Return a string with the name of the GameObject.
		* 
		* \fn const std::string& GetName() const;
		*/
		[[nodiscard]] const std::string& GetName() const;

		/*!
		* \brief Set the name of the GameObject.
		* 
		* \details Set the name of the GameObject to the string passed as a parameter.
		* 
		* \fn void SetName(const std::string& _Name);
		* 
		* \param _Name The new name of the GameObject.
		*/
		void SetName(const std::string& _Name);

		/*!
		* \brief Get the Transform of the GameObject.
		* 
		* \details Return the component Transform of the current GameObject.
		* 
		* \fn Transform& GetTransform();
		* 
		* \return Transform& a reference to the Transform of the GameObject.
		*/
		[[nodiscard]] Transform& GetTransform();

		/*!
		* \brief Get the Transform of the GameObject (const).
		*
		* \details Return the component Transform of the current GameObject.
		*
		* \fn Transform& GetTransform();
		*
		* \return Transform& a reference to the Transform of the GameObject.
		*/
		[[nodiscard]] const Transform& GetTransform() const;

		/*!
		* \brief Set the Transform of the GameObject.
		* 
		* \fn void SetTransform(const Transform& _Transform);
		* 
		* \param _Transform The new Transform of the GameObject.
		*/
		void SetTransform(const Transform& _Transform);

		/*!
		* \brief Add a tag to the GameObject.
		* 
		* \note Tags can be used to easily identify GameObjects.
		* A GameObject can have several tags, but not the same one twice.
		* 
		* \fn void AddTag(const std::string& _Tag);
		* 
		* \param _Tag The tag to be added to the GameObject.
		*/
		void AddTag(const std::string& _Tag);

		/*
		* \brief Check if the GameObject has a specific tag.
		* 
		* \fn bool HasTag(const std::string& _Tag) const;
		* 
		* \param _Tag The tag to be checked.
		* 
		* \return bool True if the GameObject has the tag, false otherwise.
		*/
		[[nodiscard]] bool HasTag(const std::string& _Tag) const;

		/*
		* \brief Remove a tag from the GameObject.
		* 
		* \fn void RemoveTag(const std::string& _Tag);
		* 
		* \param _Tag The tag to be removed from the GameObject.
		*/
		void RemoveTag(const std::string& _Tag);

		/*!
		* \brief Check if the GameObject is active.
		* 
		* \note An inactive GameObject will not be updated.
		* 
		* \fn bool IsActive() const;
		* 
		* \return bool True if the GameObject is active, false otherwise.
		*/
		[[nodiscard]] bool IsActive() const;

		/*!
		* \brief Set the GameObject to active or inactive.
		* 
		* \fn void SetActive(bool _IsActive);
		* 
		* \param _IsActive True to set the GameObject to active, false to set it to inactive.
		*/
		void SetActive(bool _IsActive);

		/*!
		* \brief Get the UUID of the GameObject.
		* 
		* \details Each GameObject has a UUID that identifies it.
		* It is generated at creation and can be retrieved with the 'GameObject::GetUUID()' method.
		* 
		* \fn uuids::uuid GetUUID() const;
		* 
		* \return uuids::uuid The UUID of the GameObject.
		*/
		[[nodiscard]] uuids::uuid GetUUID() const;

		/*
		* \brief This method logs the data linked to this GameObject.
		*
		* \details Displays the name, parent, tagsDisplays name, parent, UUID, tags and whether active or not.
		* 
		* \fn GetData(bool _ForceLoggerDraw) const
		*
		* \param _ForceLoggerDraw indicates whether the info should be put
		* in the stack to be displayed at the next engine cycle,
		* or whether it should be displayed now.
		*/
		void GetData(bool _ForceLoggerDraw) const;

		/*!
		* \brief Get all the components of the GameObject.
		* 
		* \details Return a vector with all the components of the GameObject.
		* 
		* \fn std::vector<IComponent*> GetAllComponents() const;
		* 
		* \return std::vector<IComponent*> A vector with all the components of the GameObject.
		*/
		[[nodiscard]] std::vector<IComponent*> GetAllComponents() const;

		// ECS methods

		/*!
		* \brief Add a component to the GameObject.
		* 
		* \details Add a component of the type passed as a template parameter to the GameObject.
		* 
		* \fn template <typename Component> Component* AddComponent()
		* 
		* \tparam Component The type of the component to be added.
		* 
		* \note The 'Transform' component cannot be manually added to a GameObject,
		* since a GameObject can only have one component of the same type, and
		* the 'Transform' component is already added automatically when a GameObject is created.
		*/
		template <typename Component>
		Component* AddComponent();

		/*!
		* \brief Get a component of the GameObject.
		* 
		* \details Return a pointer to the component of the type passed as a template parameter.
		* 
		* \fn template <typename Component> Component* GetComponent() const
		* 
		* \tparam Component The type of the component to be retrieved.
		* 
		* \return Component* A pointer to the component of the GameObject.
		*/
		template <typename Component>
		[[nodiscard]] Component* GetComponent() const;

		/*!
		* \brief Remove a component from the GameObject.
		* 
		* \details Remove a component of the type passed as a template parameter from the GameObject.
		* 
		* \fn template <typename Component> void RemoveComponent()
		* 
		* \tparam Component The type of the component to be removed.
		* 
		* \return Component* A pointer to the component of the GameObject.
		* 
		* \note The 'Transform' component cannot be removed from a GameObject.
		*/
		template <typename Component>
		void RemoveComponent();

		// Methods

		/*
		* \brief This is the method that will be executed every frame.
		*
		* \details This method is called at each engine cycle for all gameplay-side GameObjects.
		* 
		* \note This method is purely virtual and must be implemented in every comoponent.
		*
		* \fn virtual void Update(float _DeltaTime) = 0;
		*/
		virtual void Tick(float _DeltaTime);

		/*!
		* \brief This method is called when the GameObject receives a collision event.
		* 
		* \details This method is virtual, so it can be redefined in any class that inherits from GameObject,
		* in order to have a different behavior in each class.
		* 
		* \fn virtual void OnCollisionEnter(const S_CollisionData* _CollisionData);
		* 
		* \param _CollisionData The data of the collision event.
		*/
		virtual void OnCollisionEnter(const S_CollisionData* _CollisionData);

		/*!
		* \brief This method is called for destroying the GameObject.
		* 
		* \fn void Destroy(const frost::core::AuthorizationBadge<frost::core::SceneManager>&);
		* 
		* \param frost::core::AuthorizationBadge<frost::core::SceneManager>& The badge that authorizes the destruction of the GameObject.
		* 
		* \note This method is called by the SceneManager to destroy the GameObject.
		*/
		void Delete(const frost::core::AuthorizationBadge<frost::core::SceneManager>&);

	private:

		uuids::uuid m_uuid;
		std::string m_name;
		std::vector<IComponent*> m_components;
		std::unordered_set<std::string> m_tags;
		bool m_isActive = true;

	};
}

#include "GameObject.hxx"