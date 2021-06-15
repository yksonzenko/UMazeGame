// Engine
// Ubisoft GameDev
// by Yevheniia Ksonzenko

#include "InputManager.hpp"

namespace Engine
{
	InputManager::InputManager(::MiniKit::Engine::Context* context) noexcept
	{
		window_ = &context->GetWindow();
		window_->AddResponder(*this);
	}

	InputManager::InputManager(const InputManager&, ::MiniKit::Engine::Context* context) noexcept
	{
		window_ = &context->GetWindow();
		window_->AddResponder(*this);
	}
	
	void InputManager::KeyDown(MiniKit::Platform::Window& window, const MiniKit::Platform::KeyEvent& keyPressed) noexcept
	{
		if (keyPressed.keycode == ::MiniKit::Platform::Keycode::KeyEscape)
		{
			window.GetContext().Terminate();
		}
		
		const auto it = std::find(keys_.begin(), keys_.end(), keyPressed.keycode);
		if (it == keys_.end())
		{
			keys_.push_back(keyPressed.keycode);
		}
	}

	void InputManager::KeyUp(MiniKit::Platform::Window& window, const MiniKit::Platform::KeyEvent& event) noexcept
	{
		const auto it = std::find(keys_.begin(), keys_.end(), event.keycode);
		if (it != keys_.end())
		{
			keys_.erase(it);
		}
	}

	::MiniKit::Platform::Keycode InputManager::getKeyPressed() const
	{
		return !keys_.empty() ? keys_.back() : ::MiniKit::Platform::Keycode::Unknown;
	}

	::MiniKit::Platform::Window* InputManager::getRespondWindow() const
	{
		return window_;
	}
}
