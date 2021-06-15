#include "RenderSystem.hpp"

namespace GameEngine::ECS
{
	RenderSystem::RenderSystem()
	{
		context_ = World::getWorld()->getContext();
		commandBuffer_ = World::getWorld()->getCommandBuffer();
	}

	void RenderSystem::configure(entityx::EventManager& events)
	{
		events.subscribe<GameOverEvent>(*this);
	}

	void RenderSystem::receive(const GameOverEvent& g)
	{
		gameOver_ = g.gameOver;
	}
	
	void RenderSystem::update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt)
	{		
		delta += dt;
		commandBuffer_ = World::getWorld()->getCommandBuffer();

		entities.each<MapTileRenderer>([&](ex::Entity entity, MapTileRenderer& tileRend)
			{
				auto* view = World::getWorld()->viewPort();
			
				auto LayerIdx = 0;
				for (auto layerId : tileRend.mapLayersPack)
				{
					commandBuffer_->SetImage(*tileRend.mapTextures.at(LayerIdx));

					for (auto& tile : tileRend.transform_[LayerIdx])
					{
						if (view->setPositions(tile.tilePosition, tile.tileSize) && tile.visible)
						{
							const auto pos = view->getPosOnView();

							::MiniKit::Graphics::DrawInfo drawable;
							drawable.position = { pos.x, pos.y };
							drawable.scale = { tile.tileScale.x, tile.tileScale.y };
							drawable.angle = tile.tileRotationAngle;
							commandBuffer_->Draw(drawable, tile.texCutSet);
						}
					}
					++LayerIdx;
				}
				// draw ready sign when game starts
				if (World::getWorld()->globalTime()->getCurrentTime() < 3)
				{
					Float2 scale = { 0.0f, 0.0f };
					if (!gameOver_)
					{
						commandBuffer_->SetImage(*tileRend.mapTextures.at(2));
						scale = { 108, 18 };
					}
					else
					{
						commandBuffer_->SetImage(*tileRend.mapTextures.at(3));
						scale = { 162, 18 };
					}
					if (view->setPositions({ 14, 17 }, { 192, 32 }))
					{
						auto rPos = view->getPosOnView();

						::MiniKit::Graphics::DrawInfo drawReady;
						drawReady.position.x = rPos.x;
						drawReady.position.y = rPos.y;
						drawReady.scale = scale;
						commandBuffer_->Draw(drawReady);
					}
				}
			});
		
		entities.each<Transform, Animation>([&](ex::Entity entity, Transform& tr, Animation& anim)
			{
				commandBuffer_->SetImage(*anim.texture_);
				auto* view = World::getWorld()->viewPort();
			
				if (view->setPositions({ tr.position.x, tr.position.y}, tr.size) && anim.visible)
				{
					const auto pos = view->getPosOnView();
					const uint32_t id = ((context_->GetFrameCount() / anim.speed) % anim.texAmount) * (tr.size.x * static_cast<float>(anim.textureID));

					anim.texCutSet_.position.x = id;

					::MiniKit::Graphics::DrawInfo drawable;
					drawable.position = { pos.x,  pos.y};
					drawable.scale = { tr.scale.x, tr.scale.y };
					commandBuffer_->Draw(drawable, anim.texCutSet_);
				}
			});
		
		entities.each<Lives>([&](ex::Entity entity, Lives& lives)
			{
				commandBuffer_->SetImage(*lives.texture);
				::MiniKit::Graphics::DrawInfo drawLives;

				for (auto n = 0u; n < lives.livesCount; ++n)
				{
					drawLives.scale = { 24, 24 };
					drawLives.position = { lives.spawnPosition.x + (n * 32),  lives.spawnPosition.y };
					commandBuffer_->Draw(drawLives, lives.livesImage);
				}
			});

		// render bonus items (cherries)
		ex::ComponentHandle<MapTileRenderer> mapItems;
		auto* viewP = World::getWorld()->viewPort();
		for (ex::Entity entity : entities.entities_with_components(mapItems))
		{
			auto items = entity.component<Item>();
			commandBuffer_->SetImage(*items->texture);
			::MiniKit::Graphics::DrawInfo drawItems;
			for (auto c : items->cherryTransform_)
			{
				if (viewP->setPositions({ c.position.x,  c.position.y }, c.size) && c.visible)
				{
					const auto pos = viewP->getPosOnView();
					drawItems.scale = { 24, 24 };
					drawItems.position = { pos.x,  pos.y };
					commandBuffer_->Draw(drawItems, c.cutTexture);
				}
			}
		}
	}
}
