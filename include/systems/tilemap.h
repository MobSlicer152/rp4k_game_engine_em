#pragma once

#ifndef SYSTEMS_TILEMAP_H
#define SYSTEMS_TILEMAP_H 1

#include "engine.h"
#include "interface/button.h"

class tilemap_system : public ECS::EntitySystem {
    public:
	tilemap_system(void);

	void tick(ECS::World *world, float delta);

	void add_tile_on_click(bool has_collision, ECS::ComponentHandle<struct tilemap> map);

	~tilemap_system(void);
};

#endif
