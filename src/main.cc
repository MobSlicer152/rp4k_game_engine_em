#include <SFML/Graphics.hpp>

int main(int argc, char *argv[])
{
	sf::RenderWindow window(sf::VideoMode(1024, 600), "RP4K Game Engine");

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
				window.close();
		}
	}

	return 0;
}
