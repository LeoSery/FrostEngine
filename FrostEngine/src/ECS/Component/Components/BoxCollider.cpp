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
	}

	BoxCollider::~BoxCollider()
	{

	}

	void BoxCollider::Start()
	{
		m_currentScene = &frost::core::SceneManager::GetInstance().GetActiveScene();

		m_transform = GetParentObject().GetComponent<frost::ECS::Transform>();
		glm::mat2 RotationMatrix = GetRotationMatrix();
		m_vertices = new std::vector<glm::vec2>();

		// the transform is the center of the box, so we need to calculate the vertices based on the center
		m_vertices->push_back(((m_transform->position * RotationMatrix) + glm::vec2(-0.5, 0.5)) * m_transform->scale); // top left
		m_vertices->push_back(((m_transform->position * RotationMatrix) + glm::vec2(-0.5, -0.5)) * m_transform->scale); // bottom left
		m_vertices->push_back(((m_transform->position * RotationMatrix) + glm::vec2(0.5, -0.5)) * m_transform->scale); // bottom right
		m_vertices->push_back(((m_transform->position * RotationMatrix) + glm::vec2(0.5, 0.5)) * m_transform->scale); // top right
	}

	void BoxCollider::Update(float /*_DeltaTime*/)
	{
		if (m_isActive && !m_isStatic)
		{
			glm::mat2 RotationMatrix = GetRotationMatrix();

			m_vertices->at(0) = ((m_transform->position * RotationMatrix) + glm::vec2(-0.5, 0.5)) * m_transform->scale;
			m_vertices->at(1) = ((m_transform->position * RotationMatrix) + glm::vec2(-0.5, -0.5)) * m_transform->scale;
			m_vertices->at(2) = ((m_transform->position * RotationMatrix) + glm::vec2(0.5, -0.5)) * m_transform->scale;
			m_vertices->at(3) = ((m_transform->position * RotationMatrix) + glm::vec2(0.5, 0.5)) * m_transform->scale;
		}
	}

	void BoxCollider::Destroy()
	{

	}

	BoxCollider::CollisionData BoxCollider::IsColliding(BoxCollider& _Other)
	{
		BoxCollider::CollisionData Data = CollisionData();

		if (_Other.GetIsStatic() || !_Other.IsActive())
			return Data;

		if (!AABB(_Other))
			return Data;

		Data = SAT(_Other);
		return Data;
	}

	//bool BoxCollider::AABB(BoxCollider& _Other) const
	//{
	//	glm::vec2 min1 = m_transform->position - m_transform->scale * 0.5f;
	//	glm::vec2 max1 = m_transform->position + m_transform->scale * 0.5f;
	//	glm::vec2 min2 = _Other.m_transform->position - _Other.m_transform->scale * 0.5f;
	//	glm::vec2 max2 = _Other.m_transform->position + _Other.m_transform->scale * 0.5f;

	//	return (min1.x <= max2.x && max1.x >= min2.x) &&
	//		(min1.y <= max2.y && max1.y >= min2.y);
	//	//return (max1.x >= min2.x && min1.x <= max2.x) &&
	//	//	(max1.y >= min2.y && min1.y <= max2.y);
	//}

	bool BoxCollider::AABB(BoxCollider& _Other) const
	{
		std::vector<glm::vec2>* otherVertices = _Other.GetVertices();

		float MinX = m_vertices->at(0).x;
		float MaxX = m_vertices->at(2).x;
		float MinY = m_vertices->at(0).y;
		float MaxY = m_vertices->at(2).y;

		float otherMinX = otherVertices->at(0).x;
		float otherMaxX = otherVertices->at(2).x;
		float otherMinY = otherVertices->at(0).y;
		float otherMaxY = otherVertices->at(2).y;

		// Testez la condition de collision AABB
		return (MaxX >= otherMinX && MaxY >= otherMinY &&
			otherMaxX >= MinX && otherMaxY >= MinY);
	}

	BoxCollider::CollisionData BoxCollider::SAT(BoxCollider& _Other) const
	{
		glm::mat2 RotationMatrix = GetRotationMatrix();
		glm::mat2 RotationMatrixOther = _Other.GetRotationMatrix();

		BoxCollider::CollisionData Data = CollisionData();

		float min1;
		float max1;
		float min2;
		float max2;

		glm::vec2 axes[4] = {
			RotationMatrix * (m_vertices->at(1) - m_vertices->at(0)),
			RotationMatrix * (m_vertices->at(2) - m_vertices->at(1)),
			RotationMatrixOther * (_Other.m_vertices->at(1) - _Other.m_vertices->at(0)),
			RotationMatrixOther * (_Other.m_vertices->at(2) - _Other.m_vertices->at(1))
		};

		for (int i = 0; i < 4; i++)
		{
			min1 = glm::dot(m_vertices->at(0), axes[i]);
			max1 = min1;
			min2 = glm::dot(_Other.m_vertices->at(0), axes[i]);
			max2 = min2;

			for (int j = 1; j < 4; j++)
			{
				float projection = glm::dot(m_vertices->at(j), axes[i]);
				if (projection < min1)
					min1 = projection;
				if (projection > max1)
					max1 = projection;

				projection = glm::dot(_Other.m_vertices->at(j), axes[i]);
				if (projection < min2)
					min2 = projection;
				if (projection > max2)
					max2 = projection;
			}

			if (max1 < min2 || max2 < min1)
			{
				Data.isColliding = false;
				return Data;
			}
		}

		Data.isColliding = true;
		Data.otherCollider = &_Other;
		Data.top = max1 - min2;
		Data.bottom = max2 - min1;
		Data.left = max1 - min2;
		Data.right = max2 - min1;
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