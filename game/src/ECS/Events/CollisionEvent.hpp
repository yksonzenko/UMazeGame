#pragma once
#include <Components/Movement.hpp>

namespace GameEngine::ECS
{
	struct CollisionEvent
	{
		CollisionEvent(Movement::Direction dir)
			: curDir_(dir){}

		Movement::Direction curDir_;
	};
}
