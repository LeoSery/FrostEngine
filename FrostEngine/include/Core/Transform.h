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
        [[nodiscard]] Transform(const glm::vec2& _Position, const float& _Rotation, const glm::vec2& _Scale);

        void GetData(std::ostream& _Stream) const;

        glm::vec2 position;
        float rotation;
        glm::vec2 scale;
    };
}
