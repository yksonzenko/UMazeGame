#include "CollisionSystem.hpp"

namespace GameEngine::ECS
{
	void CollisionSystem::update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt)
	{
		entityx::ComponentHandle<MapTileRenderer> mapWallsTile;
		entityx::ComponentHandle<Transform> playerTrans;

		for (entityx::Entity walls : entities.entities_with_components(mapWallsTile))
		{
			for (entityx::Entity player : entities.entities_with_components(playerTrans))
			{
				if (player.has_component<Movement>())
				{
					onCollisionEvent(player, walls);
				}
			}
		}
	}

	void CollisionSystem::onCollisionEvent(entityx::Entity& player, entityx::Entity& walls)
	{
		auto& posX = player.component<Transform>()->position.x;
		auto& posY = player.component<Transform>()->position.y;
		
		auto playerMove = player.component<Movement>();
		auto& playerStateDir = playerMove->state;
		auto& currentDir = playerMove->currentDir;
		const auto possibleDirection = player.component<Movement>()->state.nextDirection;
		
		const auto expectedPosX = posX + playerMove->directionState.at(possibleDirection).x;
		const auto expectedPosY = posY + playerMove->directionState.at(possibleDirection).y;

		auto& wall = walls.component<MapTileRenderer>()->transform_.at(0);
		const auto mapSize = walls.component<MapTileRenderer>()->mapSize;
		
		const auto expectedPoint = static_cast<int>(expectedPosY * mapSize.x + expectedPosX);
		const auto point = static_cast<int>(posY * mapSize.x + posX);
		
		 //setting bounders to search within the map
		if (expectedPoint >= 0 && expectedPoint <= (mapSize.x * mapSize.y))
		{
			// if next direction from input is free to go, if not, player just continues running at current Dir
			if (!wall.at(expectedPoint).collidable)
			{
				currentDir = playerStateDir.nextDirection;
			}
		}

		if (point > 0 && point < (mapSize.x * mapSize.y))
		{
			// if current position is wall step back to prev position
			if (wall.at(point).collidable)
			{
				posX = playerStateDir.position.x;
				posY = playerStateDir.position.y;
			}
			if (wall.at(point).tunnel)
			{
				if (currentDir == Movement::Direction::RIGHT)
					posX = walls.component<TunnelPath>()->leftPos.x;
				if (currentDir == Movement::Direction::LEFT)
					posX = walls.component<TunnelPath>()->rightPos.x;
			}
		}
	}
}
