#include "Map.hpp"

namespace GameEngine
{
	Map::Map(Engine::Scene* scene)
	{
		mapTilesManager_ = ::std::make_unique<Engine::MapManager>("assets/images/map/pacman_map.tmx");
		mapTilesManager_->packMapLayers();
		
		mapEntity_ = scene->entities.create();
		mapEntity_.assign<MapTileRenderer>();
		mapEntity_.assign<Collision>(8.0f);
		mapEntity_.assign<TunnelPath>();
		mapEntity_.assign<Item>();
		setMapProperties();
	}

	void Map::setMapProperties()
	{
		auto comp = mapEntity_.component<MapTileRenderer>();
		
		comp->mapTextures = {
			{0, Engine::World::getWorld()->textureManager()->getImage(mapTilesManager_->getLayer(0)->getName())},
			{1, Engine::World::getWorld()->textureManager()->getImage(mapTilesManager_->getLayer(1)->getName())},
			{2, Engine::World::getWorld()->textureManager()->getImage("ready")},
			{3, Engine::World::getWorld()->textureManager()->getImage("game_over")}
		};
		
		comp->mapLayersPack = mapTilesManager_->getLayersPack();

		auto tunnel = mapEntity_.component<TunnelPath>();
		tunnel->leftPos = {0, 14};
		tunnel->rightPos = {27, 14};

		auto item = mapEntity_.component<Item>();
		
		const auto mapSize = mapTilesManager_->getMap()->getTileCount();
		comp->mapSize = { mapSize.x, mapSize.y };
		comp->transform_.resize(mapTilesManager_->getLayersList().size());

		auto layerIdx = 0;
		const auto tilesCount = mapSize.x * mapSize.y;
		comp->mapOffsets_ = Engine::World::getWorld()->viewPort()->setMapOffsets({ mapSize.x, mapSize.y }, { 16, 16 });
			
		for (auto idx : comp->mapLayersPack)
		{
			// get tileset of walls
			const auto tileSet = mapTilesManager_->getTilesetTiles(layerIdx);
			
			comp->transform_[layerIdx].resize(tilesCount);
			auto& entity = comp->transform_[layerIdx];
			
			for (auto y = 0; y != mapSize.y; ++y)
			{
				for (auto x = 0; x != mapSize.x; ++x)
				{
					const auto point = y * mapSize.x + x;
					entity[point].textureID.resize(tilesCount);
					
					// assign texture ID according to the tileset
					idx[y][x] > 0 ? (entity[point].textureID[point] = (idx[y][x] - 1)) : entity[point].textureID[point] = 0;

					for (const auto& tiles : tileSet)
					{
						if (tiles.ID == entity[point].textureID[point])
						{
							auto prop = tiles.properties;
							for (auto& p : prop)
							{
								entity[point].collidable = p.getBoolValue();
							}
						}
					}
					// detect tunnel warp
					if (idx[y][x] == 16)
					{
						entity[point].tunnel = true;
						entity[point].visible = false;
					}

					// save random positions for targeting
					if (idx[y][x] == 17)
					{
						comp->randomPoints_.push_back({static_cast<float>(x), static_cast<float>(y)});
						entity[point].visible = false;
					}

					if (idx[y][x] == 18)
					{
						item->bonuses_.push_back({ static_cast<float>(x), static_cast<float>(y) });
						entity[point].visible = false;
					}
					
					entity[point].tileRotationAngle = mapTilesManager_->getAngle(layerIdx, y * mapSize.x + x);
					entity[point].tileSize = { 16.0f, 16.0f };
					entity[point].tileScale = { 16.0f, 16.0f };
					entity[point].tilePosition.x = static_cast<float>(x);
					entity[point].tilePosition.y = static_cast<float>(y);

					entity[point].texCutSet.position.x = (entity[point].textureID[point] % 4) * entity[point].tileSize.x;
					entity[point].texCutSet.position.y = (entity[point].textureID[point] / 4) * entity[point].tileSize.y;
					entity[point].texCutSet.size.x = entity[point].tileSize.x;
					entity[point].texCutSet.size.y = entity[point].tileSize.y;
				}
			}
			++layerIdx;
		}

		// setting random positions for bonus items
		const auto randNum = rand() % 3;
		item->cherryTransform_.resize(randNum);
		item->texture = Engine::World::getWorld()->textureManager()->getImage("allSpriteSet");
		for (auto n = 0; n < randNum; ++n)
		{
			auto& tr = item->cherryTransform_.at(n);
			auto r = rand() % item->bonuses_.size();
			tr.visible = true;
			tr.amount = 1;
			tr.position = item->bonuses_.at(r);
			tr.size = { 32, 32 };
			tr.cutTexture = { {0, 224}, {32, 32} };
		}
	}
}
