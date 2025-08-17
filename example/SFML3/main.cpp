#include <texture_atlas.hpp>

#include <imgui-SFML.hpp>

#include <SFML/Graphics.hpp>

auto main() noexcept -> int
{
	sf::RenderWindow window{sf::VideoMode{{1920, 1080}}, "IMFB + SFML3"};
	sf::Clock delta_clock{};

	window.setFramerateLimit(60);

	TextureAtlas texture_atlas{};

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

		texture_atlas.show();

		window.clear({40, 44, 52});

		texture_atlas.render(window);
		ImGui::SFML::Render(window);

		window.display();
	}

	ImGui::SFML::Shutdown();
	return 0;
}
