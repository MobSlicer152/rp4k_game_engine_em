#pragma once

#ifndef INTERFACE_BUTTON_H
#define INTERFACE_BUTTON_H 1

#include <stdio.h>

#include <SFML/Graphics.hpp>

class button {
    public:
	sf::RectangleShape background;
	sf::Text text;

	bool pressed;
	bool released;
	bool clicked;
	bool highlighted;

	button(void);
	button(sf::Vector2f size, sf::Color colour, std::string text);
	~button(void);

	void highlight(sf::RenderWindow *wnd);
	void update(sf::Event event, float delta);
	void render(sf::RenderWindow *wnd, float delta);
	void check_pressed(sf::Event event);

    private:
	sf::Color default_colour;
	sf::Color highlight_colour;
};

#endif /* !INTERFACE_BUTTON_H */
