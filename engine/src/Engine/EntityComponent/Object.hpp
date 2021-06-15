#pragma once
#include <stdint.h>

namespace Engine
{
    enum class ObjectType : uint64_t {
        object = 1 << 0,
        component = 1 << 1,
        actor = 1 << 2,
    };

    class Object
    {
    protected:
        ObjectType objectType_ = ObjectType::object;

    public:
        Object(ObjectType type) : objectType_(type) {}
        virtual ~Object() = default;

        [[nodiscard]] constexpr auto getObjectType() const
        {
            return objectType_;
        }
    };
}
