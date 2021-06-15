// Engine
// Ubisoft GameDev
// by Yevheniia Ksonzenko

#include "Buttons.hpp"

namespace Engine
{
	void Button::setFlags_()
	{
		static bool no_titlebar = true;
		static bool no_scrollbar = true;
		static bool no_menu = true;
		static bool no_move = true;
		static bool no_resize = true;
		static bool no_collapse = true;
		static bool no_close = false;
		static bool no_nav = true;
		static bool no_background = true;
		static bool no_bring_to_front = true;

		if (no_titlebar)        windowFlags_ |= ImGuiWindowFlags_NoTitleBar;
		if (no_scrollbar)       windowFlags_ |= ImGuiWindowFlags_NoScrollbar;
		if (!no_menu)           windowFlags_ |= ImGuiWindowFlags_MenuBar;
		if (no_move)            windowFlags_ |= ImGuiWindowFlags_NoMove;
		if (no_resize)          windowFlags_ |= ImGuiWindowFlags_NoResize;
		if (no_collapse)        windowFlags_ |= ImGuiWindowFlags_NoCollapse;
		if (no_nav)             windowFlags_ |= ImGuiWindowFlags_NoNav;
		if (no_background)      windowFlags_ |= ImGuiWindowFlags_NoBackground;
		if (no_bring_to_front)  windowFlags_ |= ImGuiWindowFlags_NoBringToFrontOnFocus;
		if (no_close)           pOpen_ = NULL;
	}
}