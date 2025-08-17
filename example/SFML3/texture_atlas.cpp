#include <texture_atlas.hpp>

#include <print>

#include <SFML/Graphics.hpp>

#include <imgui.h>

TextureAtlas::TextureAtlas() noexcept
	: file_browser_{"TextureAtlas"},
	  current_atlas_{texture_atlas_.end()}
{
	file_browser_.set_flags(
		// ImGui::FileBrowserFlags::NO_MODAL,
		// ImGui::FileBrowserFlags::SELECT_DIRECTORY,
		ImGui::FileBrowserFlags::MULTIPLE_SELECTION,
		ImGui::FileBrowserFlags::CONFIRM_ON_ENTER,
		ImGui::FileBrowserFlags::CLOSE_ON_ESCAPE,
		ImGui::FileBrowserFlags::ALLOW_SET_WORKING_DIRECTORY,
		ImGui::FileBrowserFlags::ALLOW_CREATE,
		ImGui::FileBrowserFlags::ALLOW_RENAME,
		ImGui::FileBrowserFlags::ALLOW_DELETE
	);
	file_browser_.set_filter({".jpg", ".jpeg", ".png"});
}

auto TextureAtlas::show() noexcept -> void
{
	ImGui::Begin("TextureAtlas");
	{
		file_browser_.show();

		if (ImGui::Button("Add"))
		{
			file_browser_.open();
		}

		if (file_browser_.has_selected())
		{
			auto selected = file_browser_.get_selected();
			file_browser_.clear_selected();

			std::println("Selected: {}", selected.string());

			if (sf::Texture texture{};
				not texture.loadFromFile(selected))
			{
				std::println("Load failed");
			}
			else
			{
				current_atlas_ = texture_atlas_.emplace(std::move(selected), std::move(texture)).first;
			}
		}

		ImGui::SeparatorText("Loaded");
		if (texture_atlas_.empty())
		{
			ImGui::Text("Empty");
		}
		else
		{
			if (ImGui::BeginCombo("Select", current_atlas_->first.filename().string().c_str()))
			{
				for (auto it = texture_atlas_.begin(); it != texture_atlas_.end(); ++it)
				{
					if (const auto selected = it == current_atlas_;
						ImGui::Selectable(it->first.filename().string().c_str(), selected))
					{
						current_atlas_ = it;
					}
				}

				ImGui::EndCombo();
			}
		}
	}
	ImGui::End();
}

auto TextureAtlas::render(sf::RenderWindow& window) noexcept -> void
{
	if (current_atlas_ != texture_atlas_.end())
	{
		window.draw(sf::Sprite{current_atlas_->second});
	}
}
