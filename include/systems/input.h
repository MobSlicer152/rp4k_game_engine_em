#pragma once

#ifndef SYSTEMS_INPUT_H
#define SYSTEMS_INPUT_H 1

#include "component.h"
#include "ecs.h"
#include "engine.h"

class input_system : public ECS::EntitySystem {
    public:
	input_system(sf::RenderWindow *win);
	~input_system(void);

	void tick(ECS::World *world, float delta) override;
	void get_key_events(ECS::World *world);

    private:
	sf::RenderWindow *win;
}

#endif
