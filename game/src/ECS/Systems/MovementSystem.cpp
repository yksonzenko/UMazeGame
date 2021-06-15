#include "MovementSystem.hpp"

namespace GameEngine::ECS
{
	void MovementSystem::update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt)
	{
		time_ += dt;

		entities.each<Transform, Movement, Animation>([&](ex::Entity entity, Transform& tr, Movement& mv, Animation& anim)
			{
				// save position to step back when wall collision occurs
				mv.state.position = { tr.position.x , tr.position.y };
			
				if (time_ > mv.speed)
				{
					if (mv.currentDir != Movement::Direction::STILL)
					{
						anim.textureID = static_cast<uint8_t>(mv.currentDir);
					}
					tr.position.x += mv.directionState.at(mv.currentDir).x;
					tr.position.y += mv.directionState.at(mv.currentDir).y;
					time_ = 0;
				}
			});
	}
}