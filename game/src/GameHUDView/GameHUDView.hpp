#pragma once
#include <MiniKit/Graphics/Numerics.hpp>
#include "Engine/World/World.hpp"

namespace GameEngine
{
	class GameHUDView
	{
	public:
		GameHUDView();

		void update(int score);
		void drawExtraBonus(int bonus);
		void setPosition(::MiniKit::Graphics::float2 position);
		void showScoreOnScreen(int score);
		void showScoreDigits(int score, Float2 position);
		void showLevelOnScreen();
		void upLevel();
		void resetLevel() { level_ = 1; }
	
	private:
		
		static void collectDigits(std::vector<int>& digits, int num);
		void draw_(::MiniKit::Graphics::DrawInfo& info, ::MiniKit::Graphics::Image& image,
			bool texture) const;

		uint32_t level_{ 1 };
		::std::vector<int> digitsID_;
		::MiniKit::Graphics::Image* texture_{};
		::MiniKit::Graphics::Image* textureDSL_{}; // digits, score, level
		::MiniKit::Graphics::Rect2D<uint32_t> cutTexture_{};
		::MiniKit::Graphics::float2 position_{-1.0f, -1.0f};
		::MiniKit::Graphics::CommandBuffer* commandBuffer_;
		::MiniKit::Engine::Context* context_;
		::MiniKit::Graphics::DrawInfo drawinfo_;
		::MiniKit::Graphics::DrawInfo drawPacman_;
		float time{0.0f};
	};
}
