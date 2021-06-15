// Engine
// Ubisoft GameDev
// by Yevheniia Ksonzenko

#include "TextureManager.hpp"

namespace Engine
{
	TextureManager::TextureManager(::MiniKit::Engine::Context* context) : graphicDevice_(context->GetGraphicsDevice())
	{
		textures_.emplace("default", graphicDevice_.CreateImage("assets/images/default.png"));
	}

	void TextureManager::setImage(const ::std::string& name, const ::std::string& path)
	{
		if (textures_.count(name) == 1)
		{
			std::cout << "Texture name  \"" << name << "\"  already exists." << std::endl;
		}
		textures_.emplace(name, graphicDevice_.CreateImage(path));
	}
	
	::MiniKit::Graphics::Image* TextureManager::getImage(const ::std::string& name)
	{
		const auto search = textures_.find(name);

		if (search != textures_.end())
		{
			return textures_.at(name).get();
		}
		return textures_.at("default").get();
	}
}
