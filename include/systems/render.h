#pragma once

#ifndef SYSTEMS_RENDER_H
#define SYSTEMS_RENDER_H 1

#include <stdio.h>

#include "ecs.h"

#include "component.h"
#include "engine.h"

class render_system : public ECS::EntitySystem {
public:
	render_system(void);
	~render_system(void);

	void tick(ECS::World *world, float delta) override;

private:
	std::unordered_map<std::string, sf::Texture *> texture_map;

	sf::Texture *load_texture(std::string texture_file);
};

#endif

