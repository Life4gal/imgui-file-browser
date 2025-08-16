#include <print>

#include <imgui-file_browser.hpp>
#include <imgui-SFML.hpp>
#include <imgui.h>

#include <SFML/Graphics.hpp>

auto main() noexcept -> int
{
	sf::RenderWindow window{sf::VideoMode{{1920, 1080}}, "IMFB + SFML3"};
	sf::Clock delta_clock{};

	ImGui::FileBrowser file_browser{"FileBrowser"};

	window.setFramerateLimit(60);

	file_browser.set_flags(
		// ImGui::FileBrowserFlags::NO_MODAL,
		ImGui::FileBrowserFlags::CLOSE_ON_ESCAPE,
		ImGui::FileBrowserFlags::CONFIRM_ON_ENTER,
		ImGui::FileBrowserFlags::MULTIPLE_SELECTION,
		ImGui::FileBrowserFlags::PATH_EDITABLE
	);
	file_browser.set_filter({".hpp", ".cpp", ".dll"});

	if (not ImGui::SFML::Init(window))
	{
		return 1;
	}

	while (window.isOpen())
	{
		while (const auto event = window.pollEvent())
		{
			ImGui::SFML::ProcessEvent(window, *event);

			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
		}

			ImGui::SFML::Update(window, delta_clock.restart());

			ImGui::ShowDemoWindow();

			ImGui::Begin("IMFB");
			{
				if (ImGui::Button("Open FileBrowser"))
				{
					file_browser.open();
				}
			}
			ImGui::End();

			file_browser.show();

			if (file_browser.has_selected())
			{
				const auto selected = file_browser.get_all_selected();
				std::ranges::for_each(
					selected,
					[](const auto& path) noexcept -> void
					{
						std::println("Selected: {}", path.string());
					}
				);
				file_browser.clear_selected();
			}

			window.clear(sf::Color(40, 44, 52));

			ImGui::SFML::Render(window);

			window.display();
		}

	ImGui::SFML::Shutdown();
	return 0;
}
