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

		// Methods
		bool IsColliding(BoxCollider& _Other);

		// Getters and Setters
		[[nodiscard]] bool GetIsStatic() const;
		void SetIsStatic(bool _IsStatic);
		void GetData(bool _ForceLoggerDraw) const;
		glm::mat2 GetRotationMatrix() const;
		std::vector<glm::vec2>* GetVertices() const;

		struct CollisionData
		{
			bool top;
			bool bottom;
			bool left;
			bool right;
		};

		// Fields
		std::vector<frost::ECS::GameObject*> CollidingObjects;
		CollisionData CollisionData;
		 
	private:
		// Methods
		bool SAT(BoxCollider& _Other) const;
		bool AABB(BoxCollider& _Other) const;

		// Settings
		bool m_isStatic = false;

		// Data
		std::vector<glm::vec2>* m_vertices = nullptr;

		// Components references
		frost::ECS::Transform* m_transform = nullptr;
		frost::core::Scene* m_currentScene = nullptr;
	};
}
