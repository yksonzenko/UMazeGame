#pragma once
#include <entityx/entityx.h>
#include <MiniKit/Graphics/Numerics.hpp>
#include "Components/Transform.hpp"
#include "Components/Lives.hpp"
#include "Components/Item.hpp"
#include "Components/PlayerBehaviourMode.hpp"
#include "Components/AIBehaviourMode.hpp"
#include "Components/MapTileRenderer.hpp"
#include "Events/CollectionEvent.hpp"
#include "Events/TargetingEvent.hpp"

namespace GameEngine::ECS
{
	class ItemsCollectionSystem : public entityx::System<ItemsCollectionSystem>
	{
	public:
		ItemsCollectionSystem() = default;
		
		void update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override;
		bool collected(entityx::Entity& player, entityx::Entity& items, entityx::EventManager& events);

	private:
		uint32_t itemID_ = 0;
	};
}
