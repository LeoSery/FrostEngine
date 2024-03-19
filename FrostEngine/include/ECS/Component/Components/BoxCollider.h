#pragma once

#include "Core/SceneManagement/SceneManager.h"

#include "ECS/Component/IComponent.h"

#include "glm/mat2x2.hpp"

namespace frost::ECS
{
	class GameObject;

	class BoxCollider : public IComponent
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
		//bool BoxCollider::IsColliding(BoxCollider& _Other);

		// Getters and Setters
		[[nodiscard]] bool GetIsStatic() const;
		void SetIsStatic(bool _IsStatic);
		void GetData(bool _ForceLoggerDraw) const;
		glm::mat2 GetRotationMatrix() const;
		std::vector<glm::vec2>* GetVertices() const;
		//std::vector<glm::vec2> BoxCollider::GetAxes(const std::vector<glm::vec2>* _Vertices);
		//bool BoxCollider::SAT(BoxCollider& _Other);
		//bool BoxCollider::AABB(BoxCollider& _Other)

		// Fields
		std::vector<frost::ECS::GameObject*> CollidingObjects;
		bool isColliding = false;

	private:
		// Settings
		bool m_isStatic = false;

		// Data
		std::vector<glm::vec2>* m_vertices = nullptr;

		// Components references
		frost::ECS::Transform* m_transform = nullptr;
		frost::core::Scene* m_currentScene = nullptr;
	};
}
