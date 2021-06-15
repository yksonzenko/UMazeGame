#include "ItemsCollectionSystem.hpp"

namespace GameEngine::ECS
{	
	void ItemsCollectionSystem::update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt)
	{
		entityx::ComponentHandle<MapTileRenderer> mapItemsTile;
		entityx::ComponentHandle<Lives> lives;
		
		for (entityx::Entity items : entities.entities_with_components(mapItemsTile))
		{
			for (entityx::Entity player : entities.entities_with_components(lives))
			{
				if (collected(player, items, events))
				{
					events.emit<CollectionEvent>(player.component<Item>());
				}
			}
		}
	}
	
	bool ItemsCollectionSystem::collected(entityx::Entity& player, entityx::Entity& items, entityx::EventManager& events)
	{
		const auto posX = player.component<Transform>()->position.x;
		const auto posY = player.component<Transform>()->position.y;

		// removing eaten bonus on Pacman`s current position
		auto bonuses = items.component<Item>();
		
		for (auto& b : bonuses->cherryTransform_)
		{
			if (b.position.x == posX && b.position.y == posY
				&& b.visible)
			{
				b.visible = false;
				auto t = TargetingEvent::Type::BONUS;
				events.emit<TargetingEvent>(b.position, t);
			}
		}
		
		auto& dotsPellets = items.component<MapTileRenderer>()->transform_.at(1);
		// removing eaten item on Pacman`s current position
		for (auto& t : dotsPellets)
		{
			if (t.tilePosition.x == posX && t.tilePosition.y == posY && t.visible)
			{
				auto& v = items.component<MapTileRenderer>()->mapLayersPack.at(1);
				itemID_ = (v.at(posY).at(posX));
				if (itemID_ == 14)
				{			
					player.component<Item>()->type = Item::ItemType::Pellet;
					player.component<Item>()->pelletsAmount++;
				}
				if (itemID_ == 15)
				{
					player.component<Item>()->type = Item::ItemType::Dot;
					player.component<Item>()->dotsAmount++;
				}
				t.visible = false;
				return true;
			}
		}		
		return false;
	}
}
