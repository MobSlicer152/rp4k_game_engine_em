#pragma once

#include "SFML/Graphics/RectangleShape.hpp"
#ifndef SYSTEMS_PHYSICS_H
#define SYSTEMS_PHYSICS_H 1

#include "component.h"
#include "ecs.h"
#include "engine.h"

class physics_system : public ECS::EntitySystem {
    public:
	physics_system(void);
	~physics_system(void);

	bool
	is_colliding(ECS::ComponentHandle<struct box_collider> touching_box,
		     ECS::ComponentHandle<struct box_collider> touched_ent,
		     float x, float y);

	bool
	is_colliding(ECS::ComponentHandle<struct box_collider> touching_box,
		     sf::RectangleShape touched_rect);

	bool
	is_colliding(ECS::ComponentHandle<struct box_collider> touching_box,
		     sf::RectangleShape touched_rect, float x, float y);

	bool
	is_colliding(ECS::ComponentHandle<struct box_collider> touching_box,
		     ECS::ComponentHandle<struct box_collider> touched_box);

	void check_collision_sides(
		ECS::ComponentHandle<struct transform> trans,
		ECS::ComponentHandle<struct box_collider> touching_box,
		ECS::ComponentHandle<struct box_collider> touched_ent);

	void check_collision_sides(
		ECS::ComponentHandle<struct transform> trans,
		ECS::ComponentHandle<struct box_collider> touching_box,
		sf::RectangleShape touched_rect);

	void push_entity(ECS::Entity *touching_ent, ECS::Entity *touched_ent);

	void tick(ECS::World *world, float delta_time) override;
};

#endif /* !SYSTEMS_PHYSICS_H */
