#pragma once
#include <entityx/entityx.h>
#include "Engine/World/World.hpp"
#include "Components/AIBehaviourMode.hpp"
#include "Components/PlayerBehaviourMode.hpp"
#include "Components/Transform.hpp"
#include "Components/Lives.hpp"
#include "Components/Collision.hpp"
#include "Components/AIMovement.hpp"
#include "Components/Movement.hpp"
#include "Components/MapTileRenderer.hpp"
#include "Events/LivesEvent.hpp"
#include "Events/TargetingEvent.hpp"
#include "Events/CollectionEvent.hpp"

namespace ex = entityx;
using Float2 = ::MiniKit::Graphics::float2;

namespace GameEngine::ECS
{
	class BehaviourSystem : public ex::System<BehaviourSystem>, public ex::Receiver<BehaviourSystem>
	{
	public:
		void configure(entityx::EventManager& events) override;
		void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta dt) override;
		void receive(const CollectionEvent& collected);
	
	private:
		bool enemyAttacks(entityx::Entity& player, entityx::Entity& enemy) const;
		bool caughtEnemy(entityx::Entity& player, entityx::Entity& enemy) const;
		float getDistance(Float2& p1, Float2& p2) const;
		void changeBehaviour(ex::Entity& player, ex::Entity& enemy, ex::EventManager& events);
		void manageBehaviour(entityx::Entity& player, entityx::Entity& enemy, ex::TimeDelta dt);
		Float2 setRandomTargetPos();

		template<typename TMode, typename Tentity>
		void switchMode(TMode mode, Tentity& eBehav);

		bool changeModeToFrightened_{ false };
		int pelletAmount_{ 0 };
		::std::vector<::MiniKit::Graphics::float2> random_;
		float localTime_{ 0.0f };
	};
}
