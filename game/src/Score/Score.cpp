#include "Score.hpp"

namespace GameEngine
{
	Score::Score()
	{
		HUD_ = new GameHUDView();
	}

	void Score::update()
	{
		if (score_ <= 0)
		{
			HUD_->resetLevel();
		}
		HUD_->showScoreOnScreen(score_);
		HUD_->showLevelOnScreen();
	}
	
	void Score::addToScore(int num)
	{
		score_ += num;
	}

	void Score::resetScore()
	{
		score_ = 0;
	}

	void Score::setNewRecord()
	{
		record_ = std::max(record_, score_);
	}

	void Score::setBonus(int num)
	{
		bonus_ = num;
	}
}