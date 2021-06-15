#pragma once
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include "Engine/World/World.hpp"

namespace Engine
{
	class MapManager
	{
	public:
		explicit MapManager(const ::std::string& mapPath);

		void setMapTextures(int id, const ::std::string& name, const ::std::string& path);
		void packMapLayers();
		::std::vector<std::vector<int>> getTiles(const ::std::string& layerName);
		float getAngle(uint32_t layerIdx, uint32_t pos);
		uint32_t convertTo1D(::MiniKit::Graphics::float2 pos) const;

		[[nodiscard]] ::tmx::Layer* getLayer(std::size_t idx) const;
		[[nodiscard]] ::tmx::Map* getMap() const { return map_; }
		[[nodiscard]] ::MiniKit::Graphics::uint2 getMapSize() const { return { mapSize_}; }
		[[nodiscard]] ::std::map<::std::string, uint32_t> getLayersList() const { return layersList_; }
		[[nodiscard]] ::std::map<int, ::MiniKit::Graphics::Image*> getMapTextures() const { return mapTextures_; }
		[[nodiscard]] ::std::vector<::std::vector<::std::vector<int>>> getLayersPack() const { return layersPack; }
		[[nodiscard]] ::std::vector<::tmx::Tileset::Tile> getTilesetTiles(std::size_t layerID) const;

	private:
		void setLayersList();
		void setAngle(uint32_t layerIdx, uint32_t pos, uint32_t flag);
		uint32_t getLayerIndex(const ::std::string& layerName);

		::tmx::Map* map_ = { nullptr };
		::std::map<::std::string, uint32_t> layersList_;
		//ToDo: probably try to create vector of maps for each layer
		::std::vector<::std::map<uint32_t, float>> angle_{};
		
		::std::vector<::std::vector<::std::vector<int>>> layersPack;
		::std::map<int, ::MiniKit::Graphics::Image*> mapTextures_;
		::MiniKit::Graphics::uint2 mapSize_;
	};
}
