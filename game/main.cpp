#include <MiniKit/MiniKit.hpp>
#include "Engine/World/World.hpp"
#include "src/Menu/Menu.hpp"
#include <iostream>

namespace GameEngine {

    class GameFlow final : public ::MiniKit::Engine::Application
    {
    public:
        ::std::error_code Start(::MiniKit::Engine::Context& context) noexcept
        {
            World::getWorld()->setContext(&context);

            menu_ = ::std::make_unique<Menu::Menu>();
            World::getWorld()->gameState()->AddState(gameState_.menu, [=]() {return menu_->drawMenu(); }, true);

            std::cout << "[App]: Engine start" << std::endl;
            return {};
        }

        ::std::error_code Shutdown(::MiniKit::Engine::Context& context) noexcept
        {
            std::cout << "[App]: Engine shutdown" << std::endl;
            return {};
        }

        void Tick(::MiniKit::Engine::Context& context) noexcept
        {
            auto& commandBuffer = (context).GetGraphicsDevice().BeginFrame(0, 0, 0, 1);

            World::getWorld()->setCommandBuffer(&commandBuffer);
        	
            World::getWorld()->gameState()->Update();

            context.GetGraphicsDevice().EndFrame(commandBuffer);
        }

    private:
        ::std::unique_ptr<Menu::Menu> menu_{ nullptr };
        State gameState_{};
    };

}

int main(int argc, char** argv)
{
    GameEngine::GameFlow startGame;

    ::MiniKit::Engine::StartupInfo startupInfo{};

    startupInfo.window.title = "PAC-MAN";
    startupInfo.window.width = 960;
    startupInfo.window.height = 800;

    return ::MiniKit::ApplicationMain(startupInfo, startGame);
}