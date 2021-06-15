#pragma once
#include "Object.hpp"
#include "Component.hpp"
#include "Engine/Scene/Scene.hpp"
#include <entityx/entityx.h>
#include "ECS/Components/Transform.hpp"

namespace Engine
{
    class Actor : public Object
    {
    protected:
        Scene* scene_;
        //::std::vector<std::shared_ptr<Component>> components_;
        entityx::Entity entity_;
    	virtual void assignAllComponents() {}
        virtual void fillComponents() {}

    public:
        Actor(Scene* s) : Object(ObjectType::actor), scene_(s)
        {
            entity_ = scene_->entities.create();
            entity_.assign<GameEngine::ECS::Transform>();
        }

        explicit Actor(entityx::Entity entity);
    };
}
