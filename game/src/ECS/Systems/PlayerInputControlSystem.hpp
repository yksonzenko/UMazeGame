#pragma once
#include <entityx/entityx.h>
#include "Engine/World/World.hpp"
#include "Components/Movement.hpp"
#include "Components/Input.hpp"

namespace ex = entityx;

namespace GameEngine::ECS
{
	class PlayerInputControlSystem : public ex::System<PlayerInputControlSystem>
	{
	public:
		void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta dt) override;
	};
}
