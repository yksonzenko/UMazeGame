#pragma once

namespace GameEngine::ECS
{
	struct GameOverEvent
	{
		GameOverEvent(bool gameOver) : gameOver(gameOver) {}

		bool gameOver;
	};
}