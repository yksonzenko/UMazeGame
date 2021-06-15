#pragma once
#include "Components/Item.hpp"
#include <entityx/entityx.h>

namespace GameEngine::ECS
{
	struct CollectionEvent
	{
		CollectionEvent(entityx::ComponentHandle<Item>& item) : item(item) {}

		entityx::ComponentHandle<Item> item;
	};
}
