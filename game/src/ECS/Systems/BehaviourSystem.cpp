#include "BehaviourSystem.hpp"

namespace GameEngine::ECS
{
	void BehaviourSystem::configure(entityx::EventManager& events)
	{
		events.subscribe<CollectionEvent>(*this);
	}

	void BehaviourSystem::receive(const CollectionEvent& collected)
	{
		if (collected.item->type == Item::ItemType::Pellet && pelletAmount_ < collected.item->pelletsAmount)
		{
			pelletAmount_ = collected.item->pelletsAmount;
			changeModeToFrightened_ = true;
		}
	}
	
	void BehaviourSystem::update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta dt)
	{
		ex::ComponentHandle<AIBehaviourMode> aiBehav;
		ex::ComponentHandle<PlayerBehaviourMode> plBehav;
		ex::ComponentHandle<MapTileRenderer> mapPoint;

		for (ex::Entity map : entities.entities_with_components(mapPoint))
		{
			random_ = map.component<MapTileRenderer>()->randomPoints_;
		}

		for (ex::Entity player : entities.entities_with_components(plBehav))
		{
			for (ex::Entity enemy : entities.entities_with_components(aiBehav))
			{			
				// change behaviour for all objects
				if (enemyAttacks(player, enemy))
				{
					entities.each<AIBehaviourMode>([&](ex::Entity entity, AIBehaviourMode& ai)
						{
							changeBehaviour(player, entity, events);
						});
				}
				// change behaviour only for interacted objects
				if (caughtEnemy(player, enemy))
				{
					changeBehaviour(player, enemy, events);
				}
				manageBehaviour(player, enemy, dt);
			}
		}
		changeModeToFrightened_ = false;
	}

	float BehaviourSystem::getDistance(Float2& p1, Float2& p2) const
	{
		return static_cast<float>(std::abs(p1.x - p2.x) + std::abs(p1.y - p2.y));
	}

	bool BehaviourSystem::enemyAttacks(entityx::Entity& player, entityx::Entity& enemy) const
	{
		auto& plPos = player.component<Transform>()->position;
		auto& plRadius = player.component<Collision>()->radius_;
		auto& enPos = enemy.component<Transform>()->position;
		auto& enRadius = enemy.component<Collision>()->radius_;
		auto& enMode = enemy.component<AIBehaviourMode>()->currentMode_;

		if (getDistance(plPos, enPos) < plRadius + enRadius
			&& enMode == AIBehaviourMode::Mode::CHASE)
		{
			return true;
		}
		return false;
	}

	bool BehaviourSystem::caughtEnemy(entityx::Entity& player, entityx::Entity& enemy) const
	{
		auto& plPos = player.component<Transform>()->position;
		auto& plRadius = player.component<Collision>()->radius_;
		auto& enPos = enemy.component<Transform>()->position;
		auto& enRadius = enemy.component<Collision>()->radius_;
		auto& enMode = enemy.component<AIBehaviourMode>()->currentMode_;

		if (getDistance(plPos, enPos) < plRadius + enRadius
			&& enMode == AIBehaviourMode::Mode::FRIGHTENED)
		{
			return true;
		}
		return false;
	}

	// player collided enemy
	void BehaviourSystem::changeBehaviour(ex::Entity& player, ex::Entity& enemy, ex::EventManager& events)
	{
		ex::ComponentHandle<PlayerBehaviourMode> playerBehav = player.component<PlayerBehaviourMode>();
		ex::ComponentHandle<AIBehaviourMode> enemyBehav = enemy.component<AIBehaviourMode>();
		auto plBehav = playerBehav->allPlayerBehaviours;
		auto aiBehav = enemyBehav->allAIBehaviours;

		if (enemyBehav->currentMode_ == AIBehaviourMode::Mode::CHASE)
		{
			switchMode(AIBehaviourMode::Mode::Unknown, enemyBehav->allAIBehaviours);
			enemyBehav->localTime_ = 0;
		}

		if (playerBehav->currentMode == PlayerBehaviourMode::Mode::WALKING)
		{
			switchMode(PlayerBehaviourMode::Mode::EATEN, playerBehav->allPlayerBehaviours);
			events.emit<LivesEvent>(player.component<Lives>()->livesCount);
		}

		if (enemyBehav->currentMode_ == AIBehaviourMode::Mode::FRIGHTENED)
		{
			enemyBehav->localTime_ = 0;
			switchMode(AIBehaviourMode::Mode::EATEN, enemyBehav->allAIBehaviours);
			// if enemy was killed add extra bonuses
			auto t = TargetingEvent::Type::ENEMY;
			events.emit<TargetingEvent>(enemy.component<Transform>()->position, t);
		}
	}

	void BehaviourSystem::manageBehaviour(entityx::Entity& player, entityx::Entity& enemy, ex::TimeDelta dt)
	{
		auto enTransform = enemy.component<Transform>();
		auto enBeh = enemy.component<AIBehaviourMode>();
		auto enMove = enemy.component<AIMovement>();
		auto playerTransform = player.component<Transform>();
		auto playerBehaviour = player.component<PlayerBehaviourMode>();
		auto playerMove = player.component<Movement>();
		
		// AI behaviour
		if (enBeh->currentMode_ == AIBehaviourMode::Mode::CHASE)
		{
			enMove->targetPos = playerTransform->position;
			enBeh->localTime_ += dt;
			if (enBeh->localTime_ > enBeh->duration)
			{
				enBeh->localTime_ = 0;
				switchMode(AIBehaviourMode::Mode::SCATTER, enBeh->allAIBehaviours);
			}
			if (changeModeToFrightened_)
			{
				enBeh->localTime_ = 0;
				switchMode(PlayerBehaviourMode::Mode::CHASING, playerBehaviour->allPlayerBehaviours);
				switchMode(AIBehaviourMode::Mode::FRIGHTENED, enBeh->allAIBehaviours);
			}
		}

		if (enBeh->currentMode_ == AIBehaviourMode::Mode::SCATTER)
		{
			if (static_cast<int>(enBeh->localTime_) % 3 == 0)
			{
				auto p = setRandomTargetPos();
				enMove->targetPos = { p.x, p.y };
			}			
			enBeh->localTime_ += dt;

			if (enBeh->localTime_ > enBeh->duration)
			{
				enBeh->localTime_ = 0;
				switchMode(AIBehaviourMode::Mode::CHASE, enBeh->allAIBehaviours);
			}
			if (changeModeToFrightened_)
			{
				enBeh->localTime_ = 0;
				switchMode(PlayerBehaviourMode::Mode::CHASING, playerBehaviour->allPlayerBehaviours);
				switchMode(AIBehaviourMode::Mode::FRIGHTENED, enBeh->allAIBehaviours);
			}
		}

		if (enBeh->currentMode_ == AIBehaviourMode::Mode::FRIGHTENED)
		{
			if (static_cast<int>(enBeh->localTime_) % 3 == 0)
			{
				auto p = setRandomTargetPos();
				enMove->targetPos = { p.x, p.y };
			}
			enBeh->localTime_ += dt;
			if (changeModeToFrightened_)
			{
				enBeh->localTime_ = 0;
			}
			if (enBeh->localTime_ > enBeh->duration)
			{
				enBeh->localTime_ = 0;
				switchMode(AIBehaviourMode::Mode::CHASE, enBeh->allAIBehaviours);
			}
		}

		// wait until AI gets it`s spawn position
		if (enBeh->currentMode_ == AIBehaviourMode::Mode::EATEN
			&& enTransform->position.x == enTransform->spawnPos.x && enTransform->position.y == enTransform->spawnPos.y)
		{
			enBeh->localTime_ += dt;
			if (enBeh->localTime_ > enBeh->duration)
			{
				enBeh->localTime_ = 0;
				switchMode(AIBehaviourMode::Mode::CHASE, enBeh->allAIBehaviours);
			}
		}

		if (enBeh->currentMode_ == AIBehaviourMode::Mode::Unknown)
		{
			enBeh->localTime_ += dt;
			if (enBeh->localTime_ > enBeh->duration)
			{
				enBeh->localTime_ = 0;
				switchMode(AIBehaviourMode::Mode::WAITING, enBeh->allAIBehaviours);
			}
		}

		if (enBeh->currentMode_ == AIBehaviourMode::Mode::WAITING)
		{
			enBeh->localTime_ += dt;
			if (enBeh->localTime_ > enBeh->duration)
			{
				enBeh->localTime_ = 0;
				switchMode(AIBehaviourMode::Mode::CHASE, enBeh->allAIBehaviours);
			}
		}
		
		// Player behaviour
		if (playerBehaviour->currentMode == PlayerBehaviourMode::Mode::EATEN)
		{
			playerMove->currentDir = Movement::Direction::STILL;
			localTime_ += dt;
			if (localTime_ > playerBehaviour->duration)
			{
				localTime_ = 0;
				Engine::World::getWorld()->globalTime()->setGlobalTimer();
				switchMode(PlayerBehaviourMode::Mode::IDLE, playerBehaviour->allPlayerBehaviours);
			}
		}

		if (playerBehaviour->currentMode == PlayerBehaviourMode::Mode::IDLE)
		{
			localTime_ += dt;
			if (localTime_ > playerBehaviour->duration)
			{
				localTime_ = 0;
				switchMode(PlayerBehaviourMode::Mode::WALKING, playerBehaviour->allPlayerBehaviours);
			}
		}
		
		if (playerBehaviour->currentMode == PlayerBehaviourMode::Mode::CHASING)
		{
			if (changeModeToFrightened_)
			{
				localTime_ = 0;
			}

			localTime_ += dt;
			if ((localTime_ / 2) > 5.0f)
			{
				localTime_ = 0;
				switchMode(PlayerBehaviourMode::Mode::WALKING, playerBehaviour->allPlayerBehaviours);
			}
		}
	}

	template <typename TMode, typename Tentity>
	void BehaviourSystem::switchMode(TMode mode, Tentity& eBehav)
	{
		const auto it = eBehav.find(mode);
		if (it != eBehav.end()) {
			it->second();
		}
	}

	Float2 BehaviourSystem::setRandomTargetPos()
	{
		auto r = rand() % random_.size();
		return random_.at(r);
	}
}
