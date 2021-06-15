#pragma once

namespace GameEngine::ECS
{
	struct LivesEvent
	{
		LivesEvent(unsigned& livesLeft) : livesLeft_(livesLeft) {}

		unsigned livesLeft_{ 0 };
	};
}