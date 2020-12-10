#pragma once

#ifndef ENGINE_H
#define ENGINE_H 1

/* iostream is great and all, but I like old-school C */
#include <stdio.h>
#include <stdlib.h>

#include <SFML/Graphics.hpp>

#include "ecs.h"

#include "systems/animation.h"
#include "systems/render.h"

class engine
{
public:
	/* The window object from SFML */
	sf::RenderWindow *win;

	/* Objects for the entity component system */
	ECS::World *world;

	/*
	 * Because we prevent multiple instances by killing off the copy/move
	 * constructors and the assignment operator, we have this to give us an instance
	 */
	static engine &get_inst(void);

	/* Start the engine */
	void start(sf::RenderWindow *win);

	/* Update */
	void update(void);

	/* ECS-related functions */
	void add_system(ECS::EntitySystem *system);

private:
	bool running;

	engine(void);

	/* To prevent duplicate instances, these are just stubs */
	engine(engine &copy);
	engine(engine &&other);
	engine &operator= (engine &copy);

	~engine(void);
};

#endif /* !ENGINE_H */
