#pragma once

#include "Core/SceneManagement/SceneManager.h"
#include "Core/Export.h"

#include "ECS/Component/IComponent.h"

#include "glm/mat2x2.hpp"

namespace frost::ECS
{
	class GameObject;

	class FROST_ENGINE_API BoxCollider : public IComponent
	{
		FROST_DEFINE_RTTI(BoxCollider)

	public:

		// Constructors and Destructors
		BoxCollider(GameObject& _GameObject);
		~BoxCollider();

		// Frost engine life cycle methods
		virtual void Start() override;
		virtual void Update(float _DeltaTime) override;
		virtual void Destroy() override;

		// Structs
		struct CollisionData
		{
			bool isColliding = false;
			BoxCollider* otherCollider = nullptr;
			float top = 0.0f;
			float bottom = 0.0f;
			float left = 0.0f;
			float right = 0.0f;
		};

		// Methods
		CollisionData IsColliding(BoxCollider& _Other);

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
		CollisionData SAT(BoxCollider& _Other) const;
		BoxCollider::CollisionData AABB(BoxCollider& _Other) const;

		// Settings
		bool m_isStatic = false;

		// Data
		std::vector<glm::vec2>* m_vertices = nullptr;

		// Components references
		frost::ECS::Transform* m_transform = nullptr;
		frost::core::Scene* m_currentScene = nullptr;
	};
}
