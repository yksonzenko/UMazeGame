#pragma once

#include "Components/AIBehaviourMode.hpp"
#include "Components/PlayerBehaviourMode.hpp"

namespace GameEngine::ECS
{
	struct BehaviourEvent
	{
		BehaviourEvent(PlayerBehaviourMode::Mode& plM, AIBehaviourMode::Mode& enM)
			: playerMode_(plM), enemyMode_(enM) {}

		PlayerBehaviourMode::Mode playerMode_;
		AIBehaviourMode::Mode enemyMode_;
	};
}
