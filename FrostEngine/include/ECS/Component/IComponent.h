#pragma once

#include "Core/Internal/RTTI.h"

#define UUID_SYSTEM_GENERATOR
#include "stduuid/uuid.h"

namespace frost::ECS
{
	class GameObject;

	class IComponent : public core::RTTI
	{
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

	protected:
		[[nodiscard]] GameObject& GetParentObject() const;

	private:
		uuids::uuid m_uuid;
		GameObject& m_parentObject;
		bool m_isActive = true;
	};
}
