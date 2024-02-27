#include "Core/SceneManagement/Scene.h"

namespace frost::core
{
    Scene::Scene(const AuthorizationBadge<SceneManager>& , std::string _Name)
        : m_uuid(uuids::uuid_system_generator{}()), m_name(std::move(_Name))
    {
        m_root = new ECS::GameObject("SceneRoot", nullptr);
    }

    Scene::~Scene()
    {
        delete m_root;
    }

    Scene::Scene(Scene&& other) noexcept
    {
        m_name = std::move(other.m_name);
        m_root = other.m_root;
        m_uuid = other.m_uuid;

        other.m_root = nullptr;
    }

    Scene& Scene::operator=(Scene&& other) noexcept
    {
        if (this == &other)
            return *this;

        m_name = std::move(other.m_name);
        m_root = other.m_root;
        m_uuid = other.m_uuid;
        other.m_root = nullptr;
        return *this;
    }

    const std::string& Scene::GetName() const
    {
        return m_name;
    }

    ECS::GameObject* Scene::GetRoot() const
    {
        return m_root;
    }
}
