// Engine
// Ubisoft GameDev
// by Yevheniia Ksonzenko

#pragma once
#include <imgui.h>

namespace Engine
{
	class Button
	{
	public:
		virtual ~Button() = default;
		
		virtual void setButtons(bool* open) = 0;
		virtual void setButtonConfigs() = 0;
		void setFlags_();

		[[nodiscard]] bool getPOpen() const { return pOpen_; }
		[[nodiscard]] ImGuiWindowFlags getWinFlags() const { return windowFlags_; }

	private:
		ImGuiWindowFlags windowFlags_{ 0 };
		bool pOpen_ = true;
	};
}