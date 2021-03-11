#pragma once

#ifndef ENGINE_H
#define ENGINE_H 1

/* iostream is great and all, but I like old-school C */
#include <stdio.h>
#include <stdlib.h>

#include <SFML/Graphics.hpp>

#include "ecs.h"

#include "interface/button_map.h"
#include "interface/button.h"
#include "interface/main_camera.h"
#include "interface/pause_menu.h"
#include "interface/states.h"
#include "interface/tile.h"

#include "systems/animation.h"
#include "systems/input.h"
#include "systems/movement.h"
#include "systems/render.h"
#include "systems/tilemap.h"

class engine {
    public:
	/* The window object from SFML */
	sf::RenderWindow *win;

	/* Objects for the entity component system */
	ECS::World *world;

	main_camera *main_cam;
	pause_menu *pause;

	/*
	 * Because we prevent multiple instances by killing off the copy/move
	 * constructors and the assignment operator, we have this to give us an instance
	 */
	static engine &get_inst(void);

	/* Start the engine */
	void start(sf::RenderWindow *win);

	/* ECS-related functions */
	void add_system(ECS::EntitySystem *system);

    private:
	bool running;

	engine(void);

	/* To prevent duplicate instances, these are just stubs */
	engine(engine &copy);
	engine(engine &&other);
	engine &operator=(engine &copy);

	~engine(void);

	/* Update */
	void update(void);
	void paused_actions(void);
};

#endif /* !ENGINE_H */
