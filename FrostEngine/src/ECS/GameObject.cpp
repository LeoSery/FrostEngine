#include "ECS/Component/Components/Transform.h"
#include "Core/SceneManagement/SceneManager.h"
#include "ECS/Component/IComponent.h"
#include "ECS/Entity/GameObject.h"
#include "Utils/Logger.h"

#include <iostream>

namespace frost::ECS
{
	GameObject::GameObject(std::string _Name, GameObject* _Parent)
		: Tree<GameObject>(_Parent/* ? _Parent : core::SceneManager::GetInstance().GetActiveScene().GetRoot()*/)
		, m_name(std::move(_Name))
		, m_uuid(uuids::uuid_system_generator{}())
	{
	}

	void GameObject::Init()
	{
		AddComponent<Transform>();
		SetActive(true);
		Start();
	}

	GameObject* GameObject::New(std::string _Name, GameObject* _Parent)
	{
		GameObject* result = new GameObject(_Name, _Parent);
		result->Init();
		return result;
	}

	GameObject::~GameObject()
	{
		//Destroy();
		for (const IComponent* component : m_components)
		{
			delete component;
		}

		m_components.clear();
	}

	void GameObject::Start()
	{
		for (IComponent* component : m_components)
		{
			component->Start();
		}
	}

	void GameObject::Update(float _DeltaTime)
	{
		for (IComponent* component : m_components)
		{
			component->Update(_DeltaTime);
		}
	}

	void GameObject::Destroy()
	{
		for (IComponent* component : m_components)
		{
			component->Destroy();
		}
	}

	const std::string& GameObject::GetName() const
	{
		return m_name;
	}

	void GameObject::SetName(const std::string& _Name)
	{
		m_name = _Name;
	}

	Transform& GameObject::GetTransform()
	{
		return *GetComponent<Transform>();
	}

	const Transform& GameObject::GetTransform() const
	{
		return *GetComponent<Transform>();
	}

	void GameObject::SetTransform(const Transform& _Transform)
	{
		Transform& transformComponent = *GetComponent<Transform>();

		transformComponent.position = _Transform.position;
		transformComponent.rotation = _Transform.rotation;
		transformComponent.scale = _Transform.scale;
	}

	void GameObject::AddTag(const std::string& _Tag)
	{
		m_tags.insert(_Tag);
	}

	bool GameObject::HasTag(const std::string& _Tag) const
	{
		return m_tags.find(_Tag) != m_tags.end();
	}

	void GameObject::RemoveTag(const std::string& _Tag)
	{
		m_tags.erase(_Tag);
	}

	bool GameObject::IsActive() const
	{
		return m_isActive;
	}

	void GameObject::SetActive(bool _IsActive)
	{
		m_isActive = _IsActive;
	}

	uuids::uuid GameObject::GetUUID() const
	{
		return m_uuid;
	}

	void GameObject::GetData(bool _ForceLoggerDraw) const
	{
		frost::utils::Logger* Logger = frost::utils::Logger::GetInstance();

		Logger->LogInfo(m_name + " Infos: ");
		Logger->LogInfo("- Parent: " + (GetParent() ? GetParent()->GetName() : "None"));
		Logger->LogInfo(std::format("- UUID: {}", uuids::to_string(m_uuid)));

		Logger->LogInfo("- Name: " + m_name);

		GetTransform().GetData(false);

		std::string tags;
		tags += "- Tags: {";
		if (m_tags.empty())
		{
			tags += " None";
		}
		else
		{
			for (auto it = m_tags.begin(); it != m_tags.end(); ++it)
			{
				tags += " " + *it;

				if (std::next(it) != m_tags.end())
				{
					tags += ",";
				}
			}
		}
		tags += " }";
		Logger->LogInfo(tags);

		std::string status = m_isActive ? "True" : "False";
		Logger->LogInfo("- Active: " + status);

		if (_ForceLoggerDraw)
			Logger->Show();
	}

	std::vector<IComponent*> GameObject::GetAllComponents() const
	{
		return m_components;
	}
}