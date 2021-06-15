#include "SecondLevel.hpp"

namespace GameEngine::Levels
{
	SecondLevel::SecondLevel(Score* score)
	{
		context_ = World::getWorld()->getContext();
		systems.add(std::make_shared<LevelControlSystem>(score));
		systems.add(std::make_shared<PlayerInputControlSystem>());
		systems.add(std::make_shared<MovementSystem>());
		systems.add(std::make_shared<CollisionSystem>());
		systems.add(std::make_shared<AIMovementSystem>());
		systems.add(std::make_shared<BehaviourSystem>());
		systems.add(std::make_shared<ItemsCollectionSystem>());
		systems.add(std::make_shared<RenderSystem>());
		systems.configure();
	}

	void SecondLevel::packScene()
	{
		pacman_ = ::std::make_shared<Pacman>(this);
		map_ = ::std::make_shared<Map>(this);
		redBlinky_ = ::std::make_shared<RedBlinky>(this);
		pinkPinky_ = ::std::make_shared<PinkPinky>(this);
	}
	
	void SecondLevel::update()
	{
		systems.update<LevelControlSystem>(context_->GetFrameDelta());
		
		if (World::getWorld()->globalTime()->getCurrentTime() > 3)
		{
			systems.update<PlayerInputControlSystem>(context_->GetFrameDelta());
			systems.update<MovementSystem>(context_->GetFrameDelta());
			systems.update<CollisionSystem>(context_->GetFrameDelta());
			systems.update<AIMovementSystem>(context_->GetFrameDelta());
			systems.update<BehaviourSystem>(context_->GetFrameDelta());
			systems.update<ItemsCollectionSystem>(context_->GetFrameDelta());
		}
		systems.update<RenderSystem>(context_->GetFrameDelta());
	}
}
