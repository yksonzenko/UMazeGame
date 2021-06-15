#pragma once
#include "../GameHUDView/GameHUDView.hpp"

namespace GameEngine
{
	class Score
	{
	public:
		Score();

		void update();
		void addToScore(int num);
		void setNewRecord();
		void setBonus(int num);
		void resetScore();
		
		GameHUDView& getHUD() const { return *HUD_; }
		[[nodiscard]] int getScore() const { return score_; }
		[[nodiscard]] int getRecord() const { return record_; }
		[[nodiscard]] int getBonus() const { return bonus_; }
	
	private:
		int score_{ 0 };
		int record_{ 0 };
		int bonus_{ 0 };
		GameHUDView* HUD_;
	};
}
