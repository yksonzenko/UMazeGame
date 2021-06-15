#pragma once
#include <MiniKit/MiniKit.hpp>
#include <array>
#include "Engine/InputManager/Buttons.hpp"
#include "Engine/World/World.hpp"
#include "Game/Game.hpp"

namespace GameEngine::Menu
{
	class Menu : public Button
	{
	public:
		Menu();
		~Menu() = default;

		void drawMenu();

	private:
		void setButtons(bool* open) override;
		void setButtonConfigs() override;

		::std::unique_ptr<Game> game_{ nullptr };
		::std::unique_ptr<Button> button_{ nullptr };

		::std::unique_ptr<::MiniKit::Graphics::Image> pacmanLogoImage_{ nullptr };
		::std::array<::std::unique_ptr<::MiniKit::Graphics::Image>, 3> buttons_;

		State gState_{};
		::MiniKit::Graphics::Device& graphicsDevice_;
	};
}

