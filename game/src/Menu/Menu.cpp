#include "Menu.hpp"

namespace GameEngine::Menu
{
	Menu::Menu() : graphicsDevice_(World::getWorld()->getContext()->GetGraphicsDevice())
	{
		pacmanLogoImage_ = graphicsDevice_.CreateImage("assets/images/pacman_logo.png");
		buttons_[0] = graphicsDevice_.CreateImage("assets/images/buttons/play_button.png");
		buttons_[1] = graphicsDevice_.CreateImage("assets/images/buttons/exit_button.png");
		buttons_[2] = graphicsDevice_.CreateImage("assets/images/other/ucode_ubisoft.png");

		this->setFlags_();
	}

	void Menu::setButtonConfigs()
	{
		::ImGui::SetNextWindowPos(ImVec2(380, 300), 0);
		::ImGui::SetNextWindowSize(ImVec2(200, 200), 0);

		ImGuiStyle* style = &ImGui::GetStyle();
		style->WindowPadding = ImVec2(0, 0);

		style->Colors[ImGuiCol_Button] = ImVec4(0.14f, 0.14f, 0.14f, 0.0f);
		style->Colors[ImGuiCol_ButtonHovered] = ImVec4(1.0f, 1.0f, 1.0f, 0.10f);
		style->Colors[ImGuiCol_ButtonActive] = ImVec4(1.0f, 1.0f, 1.0f, 0.55f);
		style->Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 0.0f);
	}

	void Menu::drawMenu()
	{
		auto o = getPOpen();
		setButtons(&o);

		auto* command_buffer = World::getWorld()->getCommandBuffer();
		
		command_buffer->SetImage(*pacmanLogoImage_);
		::MiniKit::Graphics::DrawInfo drawLogo{};
		drawLogo.position.y = 300.0f;
		drawLogo.scale = { 585.8f, 124.6f };
		command_buffer->Draw(drawLogo);

		for (auto b = 0; b < 2; ++b)
		{
			command_buffer->SetImage(*buttons_[b]);
			::MiniKit::Graphics::DrawInfo button{};
			button.position = { 0.0f, 75.0f - (53.0f * b) };
			button.scale = { 180.0f, 40.0f };
			command_buffer->Draw(button);
		}

		command_buffer->SetImage(*buttons_[2]);
		::MiniKit::Graphics::DrawInfo drawULogo{};
		drawULogo.position.y = -350.0f;
		drawULogo.scale = { 144, 45 };
		command_buffer->Draw(drawULogo);
	}

	void Menu::setButtons(bool* open)
	{
		if (open)
		{
			setButtonConfigs();

			::ImGui::Begin("MENU", open, getWinFlags());

			if (ImGui::Button("PLAY", { 200.0f, 50.0f }))
			{
				game_ = ::std::make_unique<Game>();
				World::getWorld()->gameState()->AddState(gState_.play, [=]() {return game_->update(); }, true);
			}

			if (ImGui::Button("EXIT", { 200.0f, 50.0f }))
			{
				World::getWorld()->gameState()->AddState(gState_.exit, [=]() {return World::getWorld()->getContext()->Terminate(); }, true);
			}
			ImGui::End();
		}
	}
}

