#pragma once
#include <entityx/entityx.h>
#include "Events/CollisionEvent.hpp"
#include "Events/TargetingEvent.hpp"
#include "Components/AIMovement.hpp"
#include "Components/Animation.hpp"
#include "Components/Transform.hpp"
#include "Components/MapTileRenderer.hpp"
#include "../Pathfinder/AStar.hpp"

namespace GameEngine::ECS
{
	class AIMovementSystem : public entityx::System<AIMovementSystem>
	{
	public:
		void update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override;
	
	private:
		float time_{ 0.0f };
		bool targetPosChanged_{ false };
		::std::vector<Float2> posToMove_;
	};
}
