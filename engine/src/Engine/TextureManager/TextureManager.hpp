// Engine
// Ubisoft GameDev
// by Yevheniia Ksonzenko

#pragma once
#include "MiniKit/MiniKit.hpp"
#include <unordered_map>

namespace Engine
{
	class TextureManager
	{
	public:
		TextureManager(::MiniKit::Engine::Context* context);

		void setImage(const ::std::string& name, const ::std::string& path);
		::MiniKit::Graphics::Image* getImage(const ::std::string&);

	private:
		::std::unordered_map<::std::string, std::unique_ptr<::MiniKit::Graphics::Image>> textures_{};
		::MiniKit::Graphics::Device& graphicDevice_;
	};
}
