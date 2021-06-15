#pragma once
#include <entityx/entityx.h>
#include "Components/Transform.hpp"
#include "Components/Movement.hpp"
#include "Components/Animation.hpp"

namespace ex = entityx;

namespace GameEngine::ECS
{
	class MovementSystem : public ex::System<MovementSystem>
	{
	public:
		MovementSystem() = default;

		void update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override;
		
	private:
		float time_ = 0.0f;
	};
}
