#pragma once
#include <entityx/entityx.h>
#include "Engine/World/World.hpp"
#include "Events/LivesEvent.hpp"
#include "Events/GameOverEvent.hpp"
#include "Events/CollectionEvent.hpp"
#include "Events/TargetingEvent.hpp"
#include "Components/Transform.hpp"
#include "Components/AIBehaviourMode.hpp"
#include "Components/PlayerBehaviourMode.hpp"
#include "Components/Animation.hpp"
#include "../Score/Score.hpp"
#include <thread>

using namespace std::chrono_literals;
using namespace Engine;
namespace ex = entityx;

namespace GameEngine::ECS
{
	class LevelControlSystem : public ex::System<LevelControlSystem>, public ex::Receiver<LevelControlSystem>
	{
	public:
		LevelControlSystem(GameEngine::Score* score);
		
		void configure(entityx::EntityManager& entities, entityx::EventManager& events) override;
		void update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override;
		void receive(const LivesEvent& lives);
		void receive(const CollectionEvent& collectedItems);
		void receive(const TargetingEvent& target);

	private:
		bool levelCompleted_{ false };
		bool gameOver_{ false };
		bool caughtObject_{ false };
		float localTime_{ 0.0f };
		GameEngine::Score* gameScore_{nullptr};
	};
}
