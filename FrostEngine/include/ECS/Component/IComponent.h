#pragma once

/*!
* \file IComponent.h
* 
* \brief Header file for the IComponent class.
*/

#include "Core/Internal/RTTI.h"
#include "Core/Internal/export.h"

#define UUID_SYSTEM_GENERATOR
#include "stduuid/uuid.h"

/*!
* \namespace frost::ECS
*
* \brief The namespace for FrostEngine's Entity Component System.
*/
namespace frost::ECS
{
	class GameObject;

	/*!
	* \class IComponent
	* 
	* \brief The base class for all components in the FrostEngine.
	* 
	* \details This class is an abstract class that all components in the FrostEngine must inherit from.
	*/
	class FROST_ENGINE_API IComponent : public core::RTTI
	{
		/*!
		* \brief The RTTI definition for the IComponent class.
		* 
		* \def FROST_DEFINE_RTTI(IComponent) This macro defines the RTTI for the IComponent class.
		*/
		FROST_DEFINE_RTTI(IComponent);

	public:

		// Constructors and destructors
		IComponent() = delete;
		IComponent(GameObject& _GameObject);

		virtual ~IComponent();

		// Frost engine life cycle methods

		/*!
		* \brief This is the method that will be executed when the component is created.
		* 
		* \note This method is purely virtual and must be implemented in every comoponent.
		* 
		* \fn virutal void Start() = 0;
		*/
		virtual void Start() = 0;

		/*
		* \brief This is the method that will be executed every frame.
		* 
		* \note This method is purely virtual and must be implemented in every comoponent.
		* 
		* \fn virtual void Update(float _DeltaTime) = 0;
		*/
		virtual void Update(float _DeltaTime) = 0;

		// Getters and setters

		/*!
		* \brief Check if the Component is active.
		*
		* \note An inactive Compoent will not be updated.
		*
		* \fn bool IsActive() const;
		*
		* \return bool True if the Component is active, false otherwise.
		*/
		[[nodiscard]] bool IsActive() const;

		/*!
		* \brief Set the Component to active or inactive.
		*
		* \fn void SetActive(bool _IsActive);
		*
		* \param _IsActive True to set the Component to active, false to set it to inactive.
		*/
		void SetActive(bool _IsActive);

		/*!
		* \brief Get the UUID of the Component.
		*
		* \details Each Component has a UUID that identifies it.
		* It is generated at creation and can be retrieved with the 'Component::GetUUID()' method.
		*
		* \fn uuids::uuid GetUUID() const;
		*
		* \return uuids::uuid The UUID of the Component.
		*/
		[[nodiscard]] uuids::uuid GetUUID() const;

		/*!
		* \brief Get the GameObject that the Component is attached to.
		* 
		* \fn GameObject& GetParentObject() const;
		* 
		* \return GameObject& The GameObject that the Component is attached to.
		*/
		[[nodiscard]] GameObject& GetParentObject() const;

	protected:
		uuids::uuid m_uuid;
		GameObject& m_parentObject;
		bool m_isActive = true;
	};
}