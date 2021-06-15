#pragma once
#include <string>
#include "Engine/World/World.hpp"
#include "Engine/InputManager/Buttons.hpp"
#include "Levels/FirstLevel.hpp"
#include "Levels/SecondLevel.hpp"
#include "Score/Score.hpp"

namespace GameEngine
{
    class GameButtons;
	
    struct State
    {
        ::std::string menu = "menu";
        ::std::string play = "play";
        ::std::string paused = "paused";
        ::std::string resumed = "resumed";
        ::std::string gameOver = "gameOver";
        ::std::string exit = "exit";
    };

    class Game : public entityx::EntityX
    {
    public:
        Game();
    	
        void update();

    protected:
        ::std::shared_ptr<Levels::FirstLevel> firstLevel_{};
        ::std::shared_ptr<Levels::SecondLevel> secondLevel_{};
    
    private:
        static void loadTextures();

		::std::unique_ptr<GameButtons> buttons_{};
        Score* gameScore_{nullptr};
    };

	class GameButtons : public Button
	{
	public:

        void setButtonConfigs() override;
        void setButtons(bool* open) override;

        bool backToMenu{ false };
	};
}
