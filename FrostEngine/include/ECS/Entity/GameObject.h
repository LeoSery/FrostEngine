#pragma once

#include "ECS/Component/Components/Transform.h"
#include "ECS/System/Tree.h"
#include "Core/Export.h"

#define UUID_SYSTEM_GENERATOR
#include "stduuid/uuid.h"

#include <unordered_set>
#include <string>

namespace frost::ECS
{
    class IComponent;

    class FROST_ENGINE_API GameObject : public Tree<GameObject>
    {
    public:

        // Constructors and Destructors
        explicit GameObject(std::string _Name, GameObject* _Parent);
        explicit GameObject(std::string _Name);

        ~GameObject();

        // Frost engine life cycle methods
        virtual void Start();
        virtual void Update(float fDeltaTime);
        virtual void Destroy();

        // Getters and Setters
        [[nodiscard]] const std::string& GetName() const;
        void SetName(const std::string& _Name);

        [[nodiscard]] const Transform& GetTransform() const;
        void SetTransform(const Transform& _Transform);

        void AddTag(const std::string& _Tag);
        [[nodiscard]]  bool HasTag(const std::string& _Tag) const;
        void RemoveTag(const std::string& _Tag);

        [[nodiscard]] bool IsActive() const;
        void SetActive(bool _IsActive);

        [[nodiscard]] uuids::uuid GetUUID() const;
        void GetData(bool _ShowImmediately) const;

        // ECS methods
        template <typename Component>
        Component* AddComponent();

        template <typename Component>
        [[nodiscard]] Component* GetComponent() const;

        template <typename Component>
        void RemoveComponent();


    private:
        uuids::uuid m_UUID;
        std::string m_Name;
        std::vector<IComponent*> m_Components;
        std::unordered_set<std::string> m_Tags;
        bool m_isActive = true;
    };   
}

#include "GameObject.hxx"