#pragma once

#include <filesystem>
#include <unordered_map>

#include <imgui-file_browser.hpp>

#include <SFML/Graphics/Texture.hpp>

namespace sf
{
	class RenderWindow;
}

class TextureAtlas
{
public:
	using texture_atlas_type = std::unordered_map<std::filesystem::path, sf::Texture>;

private:
	ImGui::FileBrowser file_browser_;

	texture_atlas_type texture_atlas_;
	texture_atlas_type::iterator current_atlas_;

public:
	TextureAtlas() noexcept;

	auto show() noexcept -> void;

	auto render(sf::RenderWindow& window) noexcept -> void;
};
