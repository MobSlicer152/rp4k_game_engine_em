#include "interface/pause_menu.h"

pause_menu::pause_menu(void)
{
}

pause_menu::~pause_menu(void)
{
}

pause_menu::pause_menu(sf::RenderWindow *wnd)
{
	states::set_paused(false);
	this->init_buttons();
}

void pause_menu::update(sf::Event event, float delta, sf::RenderWindow *wnd)
{
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Escape)
			states::set_paused(states::get_paused() == false);
	}
}

void pause_menu::init_buttons(sf::RenderWindow *wnd)
{
	sf::Vector2f size;

	size = sf::Vector2f(wnd->getSize(), 30);

	button_map::get_map.insert(
		{ "RESUME",
		  new button(size, sf::Color(255, 135, 0, 255), "Resume") });
}

void pause_menu::quit(sf::RenderWindow *wnd)
{
	wnd->close();
}
