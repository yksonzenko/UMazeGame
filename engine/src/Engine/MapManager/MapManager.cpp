#include "MapManager.hpp"

namespace Engine
{
	MapManager::MapManager(const ::std::string& mapPath)
	{
		map_ = new tmx::Map();
		map_->load(mapPath);
		setLayersList();
	}
	
	// returns vector of tileset tiles with properties
	::std::vector<::tmx::Tileset::Tile> MapManager::getTilesetTiles(std::size_t layerID) const
	{
		return map_->getTilesets().at(layerID).getTiles();
	}

	tmx::Layer* MapManager::getLayer(std::size_t idx) const
	{
		const auto& layers = map_->getLayers();
	
		if (idx < layers.size() && layers[idx]->getType() == tmx::Layer::Type::Tile)
		{
			auto* res = layers[idx].get();			
			return res;
		}
		return nullptr;
	}

	void MapManager::setLayersList()
	{
		const auto& layers = map_->getLayers();
		uint32_t index = 0;
		
		for (const auto& layer : layers)
		{
			layersList_.insert_or_assign(layer->getName(), index);
			++index;
		}
	}

	void MapManager::packMapLayers()
	{
		mapSize_.x = map_->getTileCount().x;
		mapSize_.y = map_->getTileCount().y;
		
		const auto& layers = map_->getLayers();

		for (const auto& layer : layers)
		{
			auto lay = getTiles(layer->getName());
			layersPack.push_back(lay);
		}
	}

	void MapManager::setMapTextures(int id, const ::std::string& name, const ::std::string& path)
	{
		World::getWorld()->textureManager()->setImage(name, path);
		auto* im = World::getWorld()->textureManager()->getImage(name);
		mapTextures_.insert_or_assign(id, im);
	}

	uint32_t MapManager::getLayerIndex(const ::std::string& layerName)
	{
		const auto layer = layersList_.find(layerName);
		if (layer != layersList_.end())
		{
			return layer->second;
		}
		return -1;
	}

	//ToDo: get Layer of other types
	::std::vector<std::vector<int>> MapManager::getTiles(const ::std::string& layerName)
	{
		const auto idx = getLayerIndex(layerName);
		auto* layer = getLayer(idx);
		
		const auto& tileLayer = layer->getLayerAs<tmx::TileLayer>();
		
		const auto& mapSize = map_->getTileCount();
		const auto& tileIDs = tileLayer.getTiles();

		::std::vector<std::vector<int>> map{};
		map.resize(mapSize.y, std::vector<int>(mapSize.x));
		angle_.resize(layersList_.size());
		
		for (auto y = 0u; y < mapSize.y; ++y)
		{
			for (auto x = 0u; x < mapSize.x; ++x)
			{
				const auto position = y * mapSize.x + x;
				map[y][x] = tileIDs[position].ID;
				setAngle(idx, position, tileIDs[position].flipFlags);
			}
		}
		return map;
	}

	void MapManager::setAngle(uint32_t layerIdx, uint32_t pos, uint32_t flag)
	{
		if (flag == (tmx::TileLayer::FlipFlag::Horizontal + tmx::TileLayer::FlipFlag::Diagonal)) // 10
		{
			angle_[layerIdx][pos] = 270.0f;
		}
		else if (flag == (tmx::TileLayer::FlipFlag::Horizontal + tmx::TileLayer::FlipFlag::Vertical)) // 12
		{
			angle_[layerIdx][pos] = 180.0f;
		}
		else if (flag == (tmx::TileLayer::FlipFlag::Vertical + tmx::TileLayer::FlipFlag::Diagonal)) // 6
		{
			angle_[layerIdx][pos] = 90.0f;
		}
		else
		{
			angle_[layerIdx][pos] = 0.0f;
		}
	}

	float MapManager::getAngle(uint32_t layerIdx, uint32_t pos)
	{
		return angle_.at(layerIdx).find(pos)->second;
	}

	uint32_t MapManager::convertTo1D(::MiniKit::Graphics::float2 pos) const
	{
		return pos.y * mapSize_.x + pos.x;
	}

}
