#pragma once

namespace GameEngine::ECS
{
	struct Collision
	{
		Collision(float radius) : radius_(radius) {}

		float radius_{ 0.0f };
	};
}
