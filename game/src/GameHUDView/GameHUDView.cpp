#include "GameHUDView.hpp"

namespace GameEngine
{
	GameHUDView::GameHUDView()
	{
		texture_ = Engine::World::getWorld()->textureManager()->getImage("allSpriteSet");
		textureDSL_ = Engine::World::getWorld()->textureManager()->getImage("digits_score_level_by");
		commandBuffer_ = Engine::World::getWorld()->getCommandBuffer();
		context_ = Engine::World::getWorld()->getContext();
	}

	void GameHUDView::setPosition(const ::MiniKit::Graphics::float2 pos)
	{
		position_ = pos;
	}

	void GameHUDView::upLevel()
	{
		if (level_ <= 2)
		{
			++level_;
		}
	}

	void GameHUDView::draw_(::MiniKit::Graphics::DrawInfo& info, ::MiniKit::Graphics::Image& image,
		bool texture) const
	{
		auto* view = Engine::World::getWorld()->viewPort();
		if (view->setPositions({ info.position.x, info.position.y }, { info.scale.x, info.scale.y }))
		{
			const auto position = view->getPosOnView();
			commandBuffer_->SetImage(image);
			
			::MiniKit::Graphics::DrawInfo draw;
			draw.scale = info.scale;
			draw.position = position;
			
			if (texture)
			{
				commandBuffer_->Draw(draw, cutTexture_);
			}
			else
			{
				commandBuffer_->Draw(draw);
			}
		}
	}


	void GameHUDView::update(int score)
	{
		if (level_ > 2)
		{
			drawPacman_.scale = { 32, 32 };
			drawPacman_.position = { 0, 6 };
			cutTexture_ = { { context_->GetFrameCount() / 10 % 2 * 32 }, {32, 32} };

			for (int i = 0; i < 29; ++i)
			{
				time += context_->GetFrameDelta();
				if (time > 0.05f)
				{
					time = 0;
					drawPacman_.position.x = i;
					drawPacman_.position.y = 6;
					draw_(drawPacman_, *Engine::World::getWorld()->textureManager()->getImage("pacman"), true);
				}
			}

			// draw world TOTAL SCORE
			drawinfo_.position = { 14.5f, 0.5f };
			drawinfo_.scale = { 176, 16 };
			cutTexture_ = {{0, 3 * 16}, {176, 16}};
			draw_(drawinfo_, *textureDSL_, true);
			showScoreDigits(score, {12, 2});

			drawinfo_.position = { 14, 14 };
			drawinfo_.scale = { 400, 64 };
			draw_(drawinfo_, *Engine::World::getWorld()->textureManager()->getImage("winner"), false);

			// by
			drawinfo_.position = { 13.5, 37 };
			drawinfo_.scale = { 96, 8 };
			cutTexture_ = { {0, 4 * 16}, {192, 16} };
			draw_(drawinfo_, *textureDSL_, true);
		}
	}

	// draw extra bonus on the screen
	void GameHUDView::drawExtraBonus(int bonus)
	{
		if (bonus == 100)
		{
			cutTexture_ = { {128, 192}, {32, 32} };
		}
		if (bonus == 200)
		{
			cutTexture_ = { {0, 192}, {32, 32} };
		}
		drawinfo_.position = position_;
		drawinfo_.scale = { 32, 32 };
		draw_(drawinfo_, *texture_, true);
	}

	// collect digits one by one to draw score on screen
	void GameHUDView::collectDigits(std::vector<int>& digits, int num) {
		if (num > 9) {
			collectDigits(digits, num / 10);
		}
		digits.push_back(num % 10);
	}

	void GameHUDView::showScoreDigits(int score, Float2 position)
	{
		digitsID_.clear();
		collectDigits(digitsID_, score);
		
		// draw score digits
		for (auto idx = 0u; idx < digitsID_.size(); ++idx)
		{
			const auto s = static_cast<uint32_t>(digitsID_.at(idx));
			cutTexture_ = { {s % 10 * 16, 0}, {16, 16} };
			drawinfo_.position = { static_cast<float>(idx + position.x), position.y };
			drawinfo_.scale = { 16, 16 };
			draw_(drawinfo_, *textureDSL_, true);
		}
	}


	void GameHUDView::showScoreOnScreen(int score)
	{
		// draw world SCORE
		cutTexture_ = { {0, 16}, {80, 16} };
		drawinfo_.position = { 2, -3.5f };
		drawinfo_.scale = { 80, 16 };
		draw_(drawinfo_, *textureDSL_, true);

		showScoreDigits(score, {0.5f, -2.0f});
	}

	void GameHUDView::showLevelOnScreen()
	{
		// draw world LEVEL
		cutTexture_ = { {0, 32}, {80, 16} };
		drawinfo_.position = { 22, -2 };
		drawinfo_.scale = { 80, 16 };
		draw_(drawinfo_, *textureDSL_, true);
		
		// draw level number
		cutTexture_ = { {level_ * 16, 0}, {16, 16} };
		drawinfo_.position = { 25.5f, -2 };
		drawinfo_.scale = { 16, 16 };
		draw_(drawinfo_, *textureDSL_, true);
	}
}
