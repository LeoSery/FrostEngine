#pragma once

#include "Core/Transform.h"
#include "Core/Export.h"

#include "ECS/Tree.h"

#include <unordered_set>
#include <string>

namespace frost::ECS
{
    class FROST_ENGINE_API GameObject : public Tree<GameObject>
    {
    public:
        explicit GameObject(std::string _Name, GameObject* _Parent = nullptr, frost::core::Transform _Transform = {});

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
        std::string m_Name;
        frost::core::Transform m_Transform;
        std::unordered_set<std::string> m_Tags;
        bool m_isActive = true;
    };
}