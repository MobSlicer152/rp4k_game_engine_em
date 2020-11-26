#pragma once

#ifndef SYSTEM_RENDER_H
#define SYSTEM_RENDER_H 1

#include "ecs.h"

#include "component.h"
#include "engine.h"

class render_system : public ECS::EntitySystem {
public:
	render_system(void);
	~render_system(void);

	void tick(ECS::World *world, float delta) override;
};

#endif

