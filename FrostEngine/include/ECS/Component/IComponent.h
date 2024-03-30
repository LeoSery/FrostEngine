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
		virtual void Start() = 0;
		virtual void Update(float _DeltaTime) = 0;
		virtual void Destroy() = 0;

		// Getters and setters
		[[nodiscard]] bool IsActive() const;
		void SetActive(bool _IsActive);

		[[nodiscard]] uuids::uuid GetUUID() const;

		[[nodiscard]] GameObject& GetParentObject() const;

	protected:
		uuids::uuid m_uuid;
		GameObject& m_parentObject;
		bool m_isActive = true;
	};
}