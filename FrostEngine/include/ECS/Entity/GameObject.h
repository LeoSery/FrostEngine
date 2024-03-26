#pragma once

#include "ECS/Component/Components/Transform.h"
#include "ECS/System/Tree.h"
#include "Core/Export.h"

#define UUID_SYSTEM_GENERATOR
#include "stduuid/uuid.h"

#include <unordered_set>
#include <string>

namespace frost::ECS
{
	class IComponent;
	struct CollisionData;

	class FROST_ENGINE_API GameObject : public Tree<GameObject>
	{
	protected:
		// Constructors and Destructors
		explicit GameObject(std::string _Name, GameObject* _Parent = nullptr);
		void Init();

	public:
		static GameObject* New(std::string _Name, GameObject* _Parent);

		~GameObject();

		// Frost engine life cycle methods
		virtual void Start();
		void Update(float _DeltaTime);
		virtual void Destroy();

		// Getters and Setters
		[[nodiscard]] const std::string& GetName() const;
		void SetName(const std::string& _Name);

		[[nodiscard]] Transform& GetTransform();
		[[nodiscard]] const Transform& GetTransform() const;
		void SetTransform(const Transform& _Transform);

		void AddTag(const std::string& _Tag);
		[[nodiscard]] bool HasTag(const std::string& _Tag) const;
		void RemoveTag(const std::string& _Tag);

		[[nodiscard]] bool IsActive() const;
		void SetActive(bool _IsActive);

		[[nodiscard]] uuids::uuid GetUUID() const;
		void GetData(bool _ForceLoggerDraw) const;

		[[nodiscard]] std::vector<IComponent*> GetAllComponents() const;

		// ECS methods
		template <typename Component>
		Component* AddComponent();

		template <typename Component>
		[[nodiscard]] Component* GetComponent() const;

		template <typename Component>
		void RemoveComponent();

		// Methods
		virtual void Tick(float _DeltaTime);
		virtual void OnCollisionEnter(const CollisionData* _CollisionData);

	private:
		uuids::uuid m_uuid;
		std::string m_name;
		std::vector<IComponent*> m_components;
		std::unordered_set<std::string> m_tags;
		bool m_isActive = true;
	};
}

#include "GameObject.hxx"