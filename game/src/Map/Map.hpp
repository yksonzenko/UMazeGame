#pragma once
#include "Engine/EntityComponent/Actor.hpp"
#include "Engine/MapManager/MapManager.hpp"
#include "ECS/Components/MapTileRenderer.hpp"
#include "ECS/Components/Collision.hpp"
#include "ECS/Components/TunnelPath.hpp"
#include "ECS/Components/Item.hpp"

using Int2 = ::MiniKit::Graphics::int2;
using Float2 = ::MiniKit::Graphics::float2;
using namespace GameEngine::ECS;

namespace GameEngine
{
	class Map
	{		
	public:
		explicit Map(Engine::Scene* scene);

	private:
		void setMapProperties();

		entityx::Entity mapEntity_;
		::std::unique_ptr<Engine::MapManager> mapTilesManager_{ nullptr };
	};
}
