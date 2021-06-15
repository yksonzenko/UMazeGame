#pragma once
#include <MiniKit/Platform/Keyboard.hpp>

namespace GameEngine::ECS
{
	struct Input
	{
		::MiniKit::Platform::Keycode keyPressed_{ MiniKit::Platform::Keycode::Unknown };
	};
}
