#pragma once

#include "ECS/System/Tree.h"
#include "Core/Transform.h"
#include "Core/Export.h"

#define UUID_SYSTEM_GENERATOR
#include "stduuid/uuid.h"

#include <unordered_set>
#include <string>

namespace frost::ECS
{
    class FROST_ENGINE_API GameObject : public Tree<GameObject>
    {
    public:
        explicit GameObject(std::string _Name, GameObject* _Parent, frost::core::Transform _Transform = {});
        explicit GameObject(std::string _Name, frost::core::Transform _Transform = {});

        [[nodiscard]] const std::string& GetName() const;
        void SetName(const std::string& _Name);

        [[nodiscard]] const frost::core::Transform& GetTransform() const;
        void SetTransform(const frost::core::Transform& _Transform);

        void AddTag(const std::string& _Tag);
        [[nodiscard]]  bool HasTag(const std::string& _Tag) const;
        void RemoveTag(const std::string& _Tag);

        [[nodiscard]] bool IsActive() const;
        void SetActive(bool _IsActive);

        void GetData(std::ostream& _Stream) const;

    private:
        uuids::uuid m_UUID;
        std::string m_Name;
        frost::core::Transform m_Transform;
        std::unordered_set<std::string> m_Tags;
        bool m_isActive = true;
    };
}