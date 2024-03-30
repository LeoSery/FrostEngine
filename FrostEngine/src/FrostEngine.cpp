#include "FrostEngine.h"

#include <Core/Input/Input.h>
#include <functional>

namespace frost
{
	void Application::Init(const S_InitData& _data)
	{
		m_Window = new frost::core::Window({ _data.title.c_str(), _data.size });
		frost::core::Input::GetInstance()->init(m_Window);
		m_RenderDevice = frost::render::RenderDevice::GetInstance();
		m_RenderDevice->Init(m_Window);
		m_SceneManager = &frost::core::SceneManager::GetInstance();
		m_CurrentScene = &m_SceneManager->GetActiveScene();

#ifdef _DEBUG 
		m_Editor = frost::editor::Editor::GetInstance();
		m_Editor->Init(m_Window);
#endif	
	}

	void Application::Run()
	{
		std::chrono::steady_clock::time_point lastUpdateTime = std::chrono::steady_clock::now();

		do
		{
			/*Calculate delta time*/
			auto  now = std::chrono::steady_clock::now();
			float deltaTime = std::chrono::duration<float, std::chrono::seconds::period>(now - lastUpdateTime).count();
			lastUpdateTime = now;

			ObjectsToUpdate.clear();

			/*User Update()*/
			Update(deltaTime);

			/*GameObjects Update()*/
			if (m_CurrentScene != nullptr)
			{
				for (auto* child : m_CurrentScene->GetRoot()->GetChildren())
				{
					BrowseAllGameObjects(child, deltaTime);
				}
			}

			//Physics Update()
			PhysUpdate();

			/*Input Update()*/
			frost::core::Input::GetInstance()->Update();

			/*Render Update()*/
			m_RenderDevice->Update();

#ifdef _DEBUG
			/*Editor Update()*/
			m_Editor->DrawEditor();
			 
			/*Logger Update()*/
			frost::utils::Logger::GetInstance()->Show();
#endif 
		} while (m_Window->PollEvents());
	}

	void Application::Shutdown()
	{
#ifdef _DEBUG	
		m_Editor->Shutdown();
		delete m_Editor;
#endif
		delete m_RenderDevice;
		delete m_Window;
	}

	void Application::BrowseAllGameObjects(frost::ECS::GameObject* _GameObject, float _DeltaTime)
	{
		if (!_GameObject)
			return;

		ObjectsToUpdate.push_back(_GameObject);

		if (_GameObject->IsActive())
			_GameObject->Update(_DeltaTime);

		for (auto* child : _GameObject->GetChildren())
		{
			if (child->IsActive())
				BrowseAllGameObjects(child, _DeltaTime);
		}
	}

	void Application::PhysUpdate()
	{
		std::map < frost::ECS::BoxCollider*, std::vector < frost::ECS::S_CollisionData >> Hits;

		/*
		* For each object in the scene, check if it has a BoxCollider component.
		* If it does, check if it collides with all other objects in the scene.
		* If it does, add it to the 'Hits' map, with a 'CollisionData' vector
		* for each object with which it collides.
		*/
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
						auto CollisionData = boxCollider->IsColliding(*otherBoxCollider);
						if (CollisionData.isColliding)
						{
							Hits[boxCollider].push_back(CollisionData);
						}
					}
				}
			}
		}

		/*
		Foreach element on Hits map, iterate on the vector
		find the largets value on each field of CollisionData
		*/
		for (auto& [boxCollider, collisions] : Hits)
		{
			auto* transform = boxCollider->GetParentObject().GetComponent<frost::ECS::Transform>();

			if (transform && !transform->isMovingEntity)
				continue;

			frost::ECS::S_CollisionData largestCollision = { false, 0, 0, 0, 0 };

			for (auto& collision : collisions)
			{
				boxCollider->GetParentObject().OnCollisionEnter(&collision);

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
			if (transform)
			{
				float absTop = abs(largestCollision.top);
				float absBottom = abs(largestCollision.bottom);
				float absLeft = abs(largestCollision.left);
				float absRight = abs(largestCollision.right);

				/*
				Find the smallest overlap with the other object and move the target object
				by this offset so that it no longer collides.
				*/
				if (absTop < absBottom && absTop < absLeft && absTop < absRight && absTop != 0)
					transform->position.y -= abs(largestCollision.top);
				else if (absBottom < absTop && absBottom < absLeft && absBottom < absRight && absBottom != 0)
					transform->position.y += abs(largestCollision.bottom);
				else if (absLeft < absTop && absLeft < absBottom && absLeft < absRight && absLeft != 0)
					transform->position.x += abs(largestCollision.left);
				else if (absRight < absTop && absRight < absBottom && absRight < absLeft && absRight != 0)
					transform->position.x -= abs(largestCollision.right);
			}
		}
	}
}
