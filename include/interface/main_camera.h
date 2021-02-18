#pragma once

#ifndef INTERFACE_MAIN_CAMERA_H
#define INTERFACE_MAIN_CAMERA_H 1

#include <SFML/Graphics.hpp>

#include "ecs.h"

class main_camera {
public:
	sf::View view;

	main_camera(void);
	main_camera(sf::Vector2f pivot);
	~main_camera(void);

	void update(ECS::World *world, float delta, sf::RenderWindow *wnd);
};

#endif /* !INTERFACE_MAIN_CAMERA_H */
