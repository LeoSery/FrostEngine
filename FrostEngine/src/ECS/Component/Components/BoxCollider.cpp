#include "ECS/Component/Components/BoxCollider.h"
#include "ECS/Entity/GameObject.h"

#include "Utils/Logger.h"

#include "glm/mat2x2.hpp"
#include "glm/vec2.hpp"

namespace frost::ECS
{
	BoxCollider::BoxCollider(GameObject& _GameObject) : IComponent(_GameObject)
	{

	}

	BoxCollider::~BoxCollider()
	{

	}

	void BoxCollider::Start()
	{
		m_currentScene = &frost::core::SceneManager::GetInstance().GetActiveScene();

		m_transform = GetParentObject().GetComponent<frost::ECS::Transform>();
		glm::mat2 RotationMatrix = GetRotationMatrix();

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

    //bool BoxCollider::IsColliding(BoxCollider& _Other)
    //{
    //    /*if (!AABB(_Other))
    //        return false;*/

    //   /* return SAT(_Other);*/
    //}

    //bool BoxCollider::AABB(BoxCollider& _Other)
    //{
    //    // Calculate minimum and maximum extents for both boxes
    //    glm::vec2 min1 = m_transform->position - m_transform->scale * 0.5f;
    //    glm::vec2 max1 = m_transform->position + m_transform->scale * 0.5f;
    //    glm::vec2 min2 = _Other.m_transform->position - _Other.m_transform->scale * 0.5f;
    //    glm::vec2 max2 = _Other.m_transform->position + _Other.m_transform->scale * 0.5f;

    //    // Check for overlap on both axes (x and y)
    //    return (min1.x <= max2.x && max1.x >= min2.x) &&
    //        (min1.y <= max2.y && max1.y >= min2.y);
    //}

  //  bool BoxCollider::SAT(BoxCollider& _Other)
  //  {
  //      // 2.1. Get axes for both boxes (considering potential rotation)
  //      std::vector<glm::vec2> axes1 = GetAxes(m_vertices);
  //      std::vector<glm::vec2> axes2 = GetAxes(_Other.m_vertices);

  //      // 2.2. Test each axis for separation
  //      for (const glm::vec2& axis : axes1)
		//{
  //          float minA = Project(axis, m_vertices[0]);
  //          float maxA = minA;

  //          for (int i = 1; i < 4; ++i)
		//	{
  //              float projection = Project(axis, m_vertices[i]);
  //              minA = std::min(minA, projection);
  //              maxA = std::max(maxA, projection);
  //          }

  //          float minB = Project(axis, _Other.m_vertices[0]);
  //          float maxB = minB;

  //          for (int i = 1; i < 4; ++i)
		//	{
  //              float projection = Project(axis, _Other.m_vertices[i]);
  //              minB = std::min(minB, projection);
  //              maxB = std::max(maxB, projection);
  //          }

  //          // If projections don't overlap on any axis, there's no collision
  //          if (maxA < minB || maxB < minA)
		//	{
  //              return false;
  //          }
  //      }

  //      // If no axis separates the boxes, there's collision
  //      return true;
  //  }

    /*std::vector<glm::vec2> BoxCollider::GetAxes(const std::vector<glm::vec2>* _Vertices)
    {
        std::vector<glm::vec2> axes;
        for (int i = 0; i < 4; ++i) {
            axes.push_back(glm::normalize(_Vertices->at((i + 1) % 4) - _Vertices->at(i)));
        }
        return axes;
    }*/

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
		glm::mat2 NewMatrix (glm::vec2(cos(m_transform->rotation), -sin(m_transform->rotation)), glm::vec2(sin(m_transform->rotation), cos(m_transform->rotation)));
		return NewMatrix;
	}

	std::vector<glm::vec2>* BoxCollider::GetVertices() const
	{
		return m_vertices;
	}
}