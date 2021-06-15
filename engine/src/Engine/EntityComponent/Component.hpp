#pragma once

#include "Object.hpp"

namespace Engine
{
    enum class ComponentType : uint64_t
    {
        Transform = 1 << 0,
        //Render = 1 << 1
    };

    class Component : public Object
    {
    protected:
        ComponentType cType_{};

    public:
        Component(ComponentType type) : Object(ObjectType::component), cType_(type) {}


        constexpr auto getCompType() const
        {
            return cType_;
        }
    };
}
