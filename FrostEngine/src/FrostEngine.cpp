#include "FrostEngine.h"
#include <Core/Input/Input.h>

#include <functional>

namespace FrostEngine
{
	void Application::Init(const InitData& data)
	{
		m_Window = new frost::core::Window({ data.title.c_str(), data.size });
		frost::core::Input::GetInstance()->init(m_Window);

		m_RenderDevice = frost::core::RenderDevice::GetInstance();
		m_RenderDevice->Init(m_Window);

		m_SceneManager = &frost::core::SceneManager::GetInstance();
		m_CurrentScene = &m_SceneManager->GetActiveScene();
	}

	void Application::Run()
	{
		std::chrono::steady_clock::time_point lastUpdateTime = std::chrono::steady_clock::now();

		do
		{
			// Calculate delta time
			auto  now = std::chrono::steady_clock::now();
			float deltaTime = std::chrono::duration<float, std::chrono::seconds::period>(now - lastUpdateTime).count();
			lastUpdateTime = now;

			ObjectsToUpdate.clear();

			// User Update()
			Update(deltaTime);

			// Components Update()
			if (m_CurrentScene != nullptr)
			{
				ObjectsToUpdate.push_back(m_CurrentScene->GetRoot());

				UpdateObjectComponents(m_CurrentScene->GetRoot(), deltaTime);

				for (auto* child : m_CurrentScene->GetRoot()->GetChildren())
				{
					BrowseAllComponents(child, deltaTime);
				}
			}

			//Physics Update()
			PhysUpdate();			


			frost::core::Input::GetInstance()->Update();
			// Render Update()
			m_RenderDevice->Update();

			// Logger Update()
			frost::utils::Logger::GetInstance()->Show();

		} while (m_Window->PollEvents());
	}

	void Application::Shutdown()
	{
		delete m_RenderDevice;
		delete m_Window;
	}

	void Application::BrowseAllComponents(frost::ECS::GameObject* _GameObject, float _DeltaTime)
	{
		if (!_GameObject)
			return;

		ObjectsToUpdate.push_back(_GameObject);

		UpdateObjectComponents(_GameObject, _DeltaTime);

		for (auto* child : _GameObject->GetChildren())
		{
			if (child->IsActive())
				BrowseAllComponents(child, _DeltaTime);
		}
	}

	void Application::UpdateObjectComponents(frost::ECS::GameObject* _GameObject, float _DeltaTime)
	{
		for (auto* component : _GameObject->GetAllComponents())
		{
			if (component->IsActive())
				component->Update(_DeltaTime);
		}
	}

	void Application::PhysUpdate()
	{
		std::map<frost::ECS::BoxCollider*, std::vector<frost::ECS::BoxCollider::CollisionData>> Hits;

		for (auto* object : ObjectsToUpdate)
		{
			auto* boxCollider = object->GetComponent<frost::ECS::BoxCollider>();

			if (boxCollider)
			{
				for (auto* otherObject : ObjectsToUpdate)
				{
					auto* otherBoxCollider = otherObject->GetComponent<frost::ECS::BoxCollider>();

					if (otherBoxCollider && otherObject != object)
					{
						if (boxCollider->IsColliding(*otherBoxCollider).isColliding)
						{
							Hits[boxCollider].push_back(boxCollider->IsColliding(*otherBoxCollider));
						}
					}
				}
			}
		}

		// foreach element on Hits map, iterate on the vector find the largets value on each field of CollisionData
		for (auto& [boxCollider, collisions] : Hits)
		{
			frost::ECS::BoxCollider::CollisionData largestCollision = { false, 0, 0, 0, 0 };

			for (auto& collision : collisions)
			{
				if (collision.top > largestCollision.top)
					largestCollision.top = collision.top;

				if (collision.bottom < largestCollision.bottom)
					largestCollision.bottom = collision.bottom;

				if (collision.left < largestCollision.left)
					largestCollision.left = collision.left;

				if (collision.right > largestCollision.right)
					largestCollision.right = collision.right;
			}

			// Apply the collision
			auto* transform = boxCollider->GetParentObject().GetComponent<frost::ECS::Transform>();
			transform->position.y += largestCollision.top;
			transform->position.y += largestCollision.bottom;
			transform->position.x += largestCollision.left;
			transform->position.x += largestCollision.right;
		}
	}
}