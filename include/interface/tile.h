#pragma once

#ifndef INTERFACE_TILE_H
#define INTERFACE_TILE_H 1

#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class tile {
    public:
	bool colliding;
	sf::RectangleShape area;

	tile(void);
	tile(float x, float y, float grid_size, bool colliding);
	~tile(void);

	void render(sf::RenderTarget &target);
	const bool &get_collision(void) const;
	const sf::Vector2f &get_pos(void) const;
	std::string to_string(void);
};

#endif /* !INTERFACE_TILE_H */
