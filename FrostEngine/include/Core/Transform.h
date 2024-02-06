#pragma once

#include "Core/Export.h"

#include <glm/glm.hpp>
#include <iostream>

namespace frost::core
{
    class FROST_ENGINE_API Transform
    {
    public:
        Transform() = default;
        [[nodiscard]] Transform(const glm::vec3& _Position, const glm::vec3& _Rotation, const glm::vec3& _Scale);

        void GetData(std::ostream& _Stream) const;

        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;
    };
}
