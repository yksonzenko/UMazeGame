// Engine
// Ubisoft GameDev
// by Yevheniia Ksonzenko

#pragma once

#include <MiniKit/MiniKit.hpp>
#include <vector>

namespace Engine
{
	class InputManager : protected ::MiniKit::Platform::Responder
	{
	public:
		InputManager(::MiniKit::Engine::Context* context) noexcept;
		InputManager(const InputManager&, ::MiniKit::Engine::Context* context) noexcept;

		[[nodiscard]] ::MiniKit::Platform::Keycode getKeyPressed() const;
		[[nodiscard]] ::MiniKit::Platform::Window* getRespondWindow() const;

		void KeyDown(MiniKit::Platform::Window& window, const MiniKit::Platform::KeyEvent& keyPressed) noexcept override;
		void KeyUp(MiniKit::Platform::Window& window, const MiniKit::Platform::KeyEvent& event) noexcept override;

	private:
		::MiniKit::Platform::Window* window_;
		::std::vector<::MiniKit::Platform::Keycode> keys_;
	};
}

