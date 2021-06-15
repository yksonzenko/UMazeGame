#include "LevelControlSystem.hpp"

namespace GameEngine::ECS
{
	LevelControlSystem::LevelControlSystem(GameEngine::Score* score)
		: gameScore_(score)
	{
	}
	
	void LevelControlSystem::configure(entityx::EntityManager& entities, entityx::EventManager& events)
	{
		events.subscribe<LivesEvent>(*this);
		events.subscribe<CollectionEvent>(*this);
		events.subscribe<TargetingEvent>(*this);
	}

	void LevelControlSystem::update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt)
	{
		gameScore_->update();

		if (gameOver_)
		{
			localTime_ += dt;
			events.emit<GameOverEvent>(true);
			if (localTime_ > 1.2f)
			{
				std::this_thread::sleep_for(3000ms);
				World::getWorld()->sceneManager()->deactivateCurrentScene();
				World::getWorld()->gameState()->SetActiveState("menu");
			}
		}
		
		if (levelCompleted_)
		{
			std::this_thread::sleep_for(2000ms);
			World::getWorld()->sceneManager()->deactivateCurrentScene();
			World::getWorld()->globalTime()->setGlobalTimer();
			levelCompleted_ = false;
			gameScore_->getHUD().upLevel();
		}
		if (caughtObject_)
		{
			localTime_ += dt;
			if (localTime_ < 2.0f)
			{
				gameScore_->getHUD().drawExtraBonus(gameScore_->getBonus());
			}
			else
			{
				localTime_ = 0.0f;
				caughtObject_ = false;
			}
		}
	}

	void LevelControlSystem::receive(const LivesEvent& lives)
	{
		if (lives.livesLeft_ <= 0)
		{
			gameOver_ = true;
			std::cout << "\033[1;91m[ PAC-MAN DIED ]\033[0m" << std::endl;
		}
	}

	void LevelControlSystem::receive(const CollectionEvent& collectedItems)
	{
		if (collectedItems.item->type == Item::ItemType::Dot)
		{
			gameScore_->addToScore(10);
		}
		if (collectedItems.item->type == Item::ItemType::Pellet)
		{
			gameScore_->addToScore(50);
		}
		if (collectedItems.item->dotsAmount == 294)
		{
			levelCompleted_ = true;
		}
	}

	void LevelControlSystem::receive(const TargetingEvent& target)
	{
		gameScore_->getHUD().setPosition(target.targetPos);
		caughtObject_ = true;
		
		if (target.type == target.BONUS)
		{
			gameScore_->addToScore(100);
			gameScore_->setBonus(100);
		}
		if (target.type == target.ENEMY)
		{
			gameScore_->addToScore(200);
			gameScore_->setBonus(200);
		}
	}

}