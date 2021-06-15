#pragma once

#include <functional>
#include <map>

namespace Engine::FSM
{
	class StateMachine
	{
	public:

		[[deprecated]] void SetState(const std::function<void()>& state);

		void SetActiveState(const std::string& state_id);
		void AddState(const std::string& state_id, const std::function<void()>& state, bool is_active = false);
		void Update() const;

	private:
		std::function<void()> activeState = nullptr;
		std::map<std::string, std::function<void()>> allStates;
	};
}
