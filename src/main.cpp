#include <SFML/Graphics.hpp>

int main()
{
    uint width = 800u;
    uint height = 480u;
    auto window = sf::RenderWindow({width, height}, "CMake SFML Project", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(144);
    
    uint displayWidth = sf::VideoMode::getDesktopMode().width;
    uint displayHeight = sf::VideoMode::getDesktopMode().height;
    window.setPosition(sf::Vector2i(
        static_cast<int>(displayWidth / 2 - width / 2),
        static_cast<int>(displayHeight / 2 - height / 2))
    );

    while (window.isOpen())
    {
        for (auto event = sf::Event(); window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear(sf::Color(100, 149, 237));
        window.display();
    }
}
