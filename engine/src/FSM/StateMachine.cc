#include "StateMachine.hh"

namespace Engine::FSM
{
	void StateMachine::SetState(const std::function<void()>& state)
	{
		activeState = state;
	}

	void StateMachine::SetActiveState(const std::string& state_id)
	{
		const auto search = allStates.find(state_id);

		if (search != allStates.end())
		{
			activeState = search->second;
		}
		else
		{
			::std::cout << "\033[0m[ERROR]\033[4;35m " << "state: " << state_id << " does not exist\033[0m" << std::endl;
		}
	}

	void StateMachine::AddState(const std::string& state_id, const std::function<void()>& state, bool is_active)
	{
		is_active ? SetState(allStates[state_id] = state) : allStates[state_id] = state;
	}

	void StateMachine::Update() const
	{
		if (activeState != nullptr)
		{
			activeState();
		}
	}
}
