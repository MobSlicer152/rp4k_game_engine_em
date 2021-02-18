#pragma once

#ifndef INTERFACE_PAUSE_MENU_H
#define INTERFACE_PAUSE_MENU_H 1

#include <SFML/Graphics.hpp>
#include "button.h"
#include "button_map.h"
#include "states.h"

class pause_menu {
public:
	pause_menu(void);
	pause_menu(sf::RenderWindow *wnd);
	~pause_menu(void);

	void update(sf::Event event, float delta, sf::RenderWindow *wnd);
	void render(sf::RenderWindow *wnd, float delta, sf::Vector2f resume_pos);

private:
	void init_buttons(sf::RenderWindow *wnd);
	void quit(sf::RenderWindow *wnd);
};

#endif /* !INTERFACE_PAUSE_MENU_H */
