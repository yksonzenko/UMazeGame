#include "AIMovementSystem.hpp"

namespace GameEngine::ECS
{
	void AIMovementSystem::update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt)
	{
		entityx::ComponentHandle<MapTileRenderer> mapItemsTile;
		auto mapTiles = entities.entities_with_components(mapItemsTile);
		
		entities.each<AIMovement>([&](entityx::Entity entity, AIMovement& move)
			{
				move.localTime += dt;
				if (move.targetPos.x > 0.0f && move.targetPos.y > 0.0f)
				{
					auto tr = entity.component<Transform>();

					for (auto t : mapTiles)
					{
						auto& walls = t.component<MapTileRenderer>()->transform_.at(0);
						GameEngine::AStar findPath;
						// pass map size and tiles to find shortest available path
						findPath.loadGrid(walls, t.component<MapTileRenderer>()->mapSize);

						// receive vector with the whole path to the target
						const auto nextMovePos = findPath.findPath({ tr->position }, { move.targetPos });

						if (!nextMovePos.empty() && move.localTime > move.speed)
						{
							const auto newPos = nextMovePos.begin();
	                        tr->position.x = newPos->x;
	                        tr->position.y = newPos->y;
							move.localTime = 0;
						}
					}
				}
			});
	}
}
