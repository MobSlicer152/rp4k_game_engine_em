#pragma once

#ifndef SYSTEMS_ANIMATION_H
#define SYSTEMS_ANIMATION_H 1

#include "ecs.h"

#include "component.h"

class animation_system : public ECS::EntitySystem {
    public:
	animation_system(void);
	~animation_system(void);

	void tick(ECS::World *world, float delta_time) override;
};

#endif /* !SYSTEMS_ANIMATION_H */
