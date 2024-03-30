#include "ECS/Component/Components/BoxCollider.h"
#include "ECS/Entity/GameObject.h"

#include "Utils/Logger.h"

#include "glm/mat2x2.hpp"
#include "glm/vec2.hpp"

namespace frost::ECS
{
	BoxCollider::BoxCollider(GameObject& _GameObject) : IComponent(_GameObject)
	{
		Start();
		m_collisionChannel = Default;
		
	}

	BoxCollider::~BoxCollider()
	{
		delete m_vertices;
		frost::utils::Logger::GetInstance()->LogInfo("BoxCollision destroyed.");
	}

	void BoxCollider::Start()
	{
		m_currentScene = &frost::core::SceneManager::GetInstance().GetActiveScene();
		m_transform = GetParentObject().GetComponent<frost::ECS::Transform>();
		m_vertices = new std::vector<glm::vec2>();

		// the transform is the center of the box, so we need to calculate the vertices based on the center
		m_vertices->push_back(((m_transform->position) + glm::vec2(-1.0, 1.0)) * m_transform->scale); // top left
		m_vertices->push_back(((m_transform->position) + glm::vec2(-1.0, -1.0)) * m_transform->scale); // bottom left
		m_vertices->push_back(((m_transform->position) + glm::vec2(1.0, -1.0)) * m_transform->scale); // bottom right
		m_vertices->push_back(((m_transform->position) + glm::vec2(1.0,	1.0)) * m_transform->scale); // top right
	}

	void BoxCollider::Update(float /*_DeltaTime*/)
	{
		if (m_isActive && !m_isStatic)
		{
			glm::mat2 RotationMatrix = GetRotationMatrix();

			m_vertices->at(0) = ((m_transform->position) + glm::vec2(-1.0, 1.0)) * m_transform->scale;
			m_vertices->at(1) = ((m_transform->position) + glm::vec2(-1.0, -1.0)) * m_transform->scale;
			m_vertices->at(2) = ((m_transform->position) + glm::vec2(1.0, -1.0)) * m_transform->scale;
			m_vertices->at(3) = ((m_transform->position) + glm::vec2(1.0, 1.0)) * m_transform->scale;
		}
	}


	S_CollisionData BoxCollider::IsColliding(BoxCollider& _Other)
	{
		S_CollisionData Data = S_CollisionData();

		if (_Other.GetIsStatic() || !_Other.IsActive())
			return Data;
		if (m_collisionSettings.contains(_Other.m_collisionChannel) && m_collisionSettings.at(_Other.m_collisionChannel) != CollisionResponse::Ignore)
		{
			return AABB(_Other);
		}
		else
		{
			return Data;
		}
		
	}

	S_CollisionData BoxCollider::AABB(BoxCollider& _Other) const
	{
		std::vector<glm::vec2>* otherVertices = _Other.GetVertices();
		S_CollisionData Data = S_CollisionData();

		float MinX = m_vertices->at(0).x;
		float MaxX = m_vertices->at(2).x;
		float MaxY = m_vertices->at(0).y;
		float MinY = m_vertices->at(2).y;

		float otherMinX = otherVertices->at(0).x;
		float otherMaxX = otherVertices->at(2).x;
		float otherMaxY = otherVertices->at(0).y;
		float otherMinY = otherVertices->at(2).y;

		bool AisToTheRightOfB = MinX > otherMaxX;
		bool AisToTheLeftOfB = MaxX < otherMinX;

		bool AisAboveB = MinY > otherMaxY;
		bool AisBelowB = MaxY < otherMinY;

		bool isCollide = !(AisToTheRightOfB || AisToTheLeftOfB || AisAboveB || AisBelowB);

		if (!isCollide)
			return Data;

		Data.isColliding = isCollide;
		Data.otherCollider = &_Other;
		Data.top = MaxY - otherMinY;
		Data.bottom = MinY - otherMaxY;
		Data.left = MinX - otherMaxX;
		Data.right = MaxX - otherMinX;
		return Data;
	}

	bool BoxCollider::GetIsStatic() const
	{
		return m_isStatic;
	}

	void BoxCollider::SetIsStatic(bool _IsStatic)
	{
		m_isStatic = _IsStatic;
	}

	void BoxCollider::GetData(bool _ForceLoggerDraw) const
	{
		frost::utils::Logger* Logger = frost::utils::Logger::GetInstance();

		std::string IsActiveString = " IsActive : " + m_isActive ? "True" : "False";
		std::string IsStaticString = " IsStatic : " + m_isStatic ? "True" : "False";

		Logger->LogInfo(IsActiveString);
		Logger->LogInfo(IsStaticString);

		if (_ForceLoggerDraw)
			Logger->Show();
	}

	glm::mat2 BoxCollider::GetRotationMatrix() const
	{
		glm::mat2 NewMatrix(glm::vec2(cos(m_transform->rotation), -sin(m_transform->rotation)), glm::vec2(sin(m_transform->rotation), cos(m_transform->rotation)));
		return NewMatrix;
	}

	std::vector<glm::vec2>* BoxCollider::GetVertices() const
	{
		return m_vertices;
	}
}
