#include "Game.hpp"

using namespace Engine;

namespace GameEngine
{
	Game::Game()
	{	
		loadTextures();
		buttons_ = std::make_unique<GameButtons>();
		buttons_->setFlags_();
		gameScore_ = new Score();
		World::getWorld()->sceneManager()->clearAllScenes();

		firstLevel_ = World::getWorld()->sceneManager()->createScene<Levels::FirstLevel>("firstScene", gameScore_);
		firstLevel_->activate();
		World::getWorld()->globalTime()->setGlobalTimer();
	}

	void Game::update()
	{
		auto o = buttons_->getPOpen();
		buttons_->setButtons(&o);

		World::getWorld()->globalTime()->getGlobalTime();

		// just testing draw viewport borders
		if (World::getWorld()->viewPort()->setToViewPos({ 0, 0 }, { 0, 0 }))
		{
			World::getWorld()->viewPort()->drawViewPortBoundaries(*World::getWorld()->getCommandBuffer());
		}
		//------------
		World::getWorld()->sceneManager()->updateCurrentScene();
		gameScore_->getHUD().update(gameScore_->getScore());
	}

	void Game::loadTextures()
	{
		auto* textures = World::getWorld()->textureManager();
		textures->setImage("pacman", "assets/images/sprites/pacman_set.png");
		textures->setImage("allSpriteSet", "assets/images/sprites/all_sprites_set.png");
		textures->setImage("tile_map_layer", "assets/images/map/map_tiles/map_set_16px(64x48).png");
		textures->setImage("dots_pallet_layer", "assets/images/map/map_tiles/dot_pellet_layer.png");
		textures->setImage("ready", "assets/images/other/ready.png");
		textures->setImage("game_over", "assets/images/other/game_over.png");
		textures->setImage("winner", "assets/images/other/winner.png");
		textures->setImage("digits_score_level_by", "assets/images/other/digits_score_level_by.png");
	}
	
	void GameButtons::setButtons(bool* open)
	{
		setButtonConfigs();

		::ImGui::Begin("BACK", open, getWinFlags());

		if (ImGui::Button("BACK TO MENU", { 110.0f, 50.0f }))
		{
			World::getWorld()->sceneManager()->clearAllScenes();
			World::getWorld()->gameState()->SetActiveState("menu");
		}
		::ImGui::End();
	}

	void GameButtons::setButtonConfigs()
	{
		::ImGui::SetNextWindowPos(ImVec2(25, 710), 0);
		::ImGui::SetNextWindowSize(ImVec2(110, 50), 0);

		ImGuiStyle* style = &ImGui::GetStyle();
		style->WindowPadding = ImVec2(0, 0);

		style->Colors[ImGuiCol_Button] = ImVec4(0.14f, 0.14f, 0.14f, 0.0f);
		style->Colors[ImGuiCol_ButtonHovered] = ImVec4(1.0f, 1.0f, 1.0f, 0.10f);
		style->Colors[ImGuiCol_ButtonActive] = ImVec4(1.0f, 1.0f, 1.0f, 0.55f);
		style->Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 0.7f);
	}
}