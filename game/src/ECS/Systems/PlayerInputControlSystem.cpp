#include "PlayerInputControlSystem.hpp"

namespace GameEngine::ECS
{
	void PlayerInputControlSystem::update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta dt)
	{
		const auto key = Engine::World::getWorld()->inputManager()->getKeyPressed();

		entities.each<Movement, Input>([&](ex::Entity entity, Movement& move, Input& input)
			{
				if (input.keyPressed_ != key && key != ::MiniKit::Platform::Keycode::Unknown)
				{
					input.keyPressed_ = key;
				}

				if (input.keyPressed_ == ::MiniKit::Platform::Keycode::Unknown)
				{
					move.state.nextDirection = Movement::Direction::STILL;
				}
				if (input.keyPressed_ == ::MiniKit::Platform::Keycode::KeyLeft
					|| input.keyPressed_ == ::MiniKit::Platform::Keycode::KeyA)
				{
					move.state.nextDirection = Movement::Direction::LEFT;
				}
				if (input.keyPressed_ == ::MiniKit::Platform::Keycode::KeyRight
					|| input.keyPressed_ == ::MiniKit::Platform::Keycode::KeyD)
				{
					move.state.nextDirection = Movement::Direction::RIGHT;
				}
				if (input.keyPressed_ == ::MiniKit::Platform::Keycode::KeyUp
					|| input.keyPressed_ == ::MiniKit::Platform::Keycode::KeyW)
				{
					move.state.nextDirection = Movement::Direction::UP;
				}
				if (input.keyPressed_ == ::MiniKit::Platform::Keycode::KeyDown
					|| input.keyPressed_ == ::MiniKit::Platform::Keycode::KeyS)
				{
					move.state.nextDirection = Movement::Direction::DOWN;
				}
			});
	}
}
