#pragma once

#ifndef SYSTEMS_MOVEMENT_H
#define SYSTEMS_MOVEMENT_H 1

#include "component.h"
#include "ecs.h"
#include "engine.h"

#define X_SPEED 0.3
#define Y_SPEED 0.3

class movement_system : public ECS::EntitySystem {
    public:
	movement_system(void);
	~movement_system(void);

	void tick(ECS::World *world, float delta) override;
}

#endif
