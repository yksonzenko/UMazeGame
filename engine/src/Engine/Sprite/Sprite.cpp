// Engine
// Ubisoft GameDev
// by Yevheniia Ksonzenko

#include "Sprite.hpp"

namespace Engine
{
	Sprite::Sprite(const ::std::string& textureName, const ::std::string& path)
	{
		World::getWorld()->textureManager()->setImage(textureName, path);
	}
	
	Sprite::Sprite(const ::std::string& textureName, const ::std::string& path, const Float2 position, const Float2 size, const Float2 edges)
		: rectangle_({ position }, { size }, { edges }, 0.0f)
	{
		World::getWorld()->textureManager()->setImage(textureName, path);
	}

	::MiniKit::Graphics::Image* Sprite::getImage(const ::std::string& name)
	{
		return World::getWorld()->textureManager()->getImage(name);
	}
}
