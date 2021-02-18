#include "systems/physics.h"
#include "component.h"

physics_system::physics_system(void)
{
}

bool physics_system::is_colliding(
	ECS::ComponentHandle<struct box_collider> touching_box,
	ECS::ComponentHandle<struct box_collider> touched_box, float x, float y)
{
	/* Longest return statement I have ever written */
	return (touching_box->right_edge + x > touched_box->left_edge &&
		touched_box->right_edge > touching_box->left_edge + x &&
		touching_box->bottom_edge + y > touched_box->top_edge &&
		touched_box->bottom_edge > touching_box->top_edge + y);
}

bool physics_system::is_colliding(
	ECS::ComponentHandle<struct box_collider> touching_box,
	sf::RectangleShape touched_rect, float x, float y)
{
	float touched_rect_left = touched_rect.getPosition().x;
	float touched_rect_right =
		touched_rect_left + touched_rect.getGlobalBounds().width;

	float touched_rect_top = touched_rect.getPosition().y;
	float touched_rect_bottom =
		touched_rect_top + touched_rect.getGlobalBounds().height;

	return (touching_box->right_edge + x > touched_rect_left &&
		touched_rect_right > touching_box->left_edge + x &&
		touching_box->bottom_edge + y > touched_rect_bottom &&
		touched_rect_bottom > touching_box->top_edge + y);
}

bool physics_system::is_colliding(
	ECS::ComponentHandle<struct box_collider> touching_box,
	ECS::ComponentHandle<struct box_collider> touched_box)
{
	return (touching_box->right_edge > touched_box->left_edge &&
		touched_box->right_edge > touching_box->left_edge &&
		touching_box->bottom_edge > touched_box->top_edge &&
		touched_box->bottom_edge > touching_box->top_edge);
}

void physics_system::check_collision_sides(
	ECS::ComponentHandle<struct transform> trans,
	ECS::ComponentHandle<struct box_collider> touching_box,
	ECS::ComponentHandle<struct box_collider> touched_box)
{
	if (trans->x_speed > 0 &&
	    touching_box->right_edge + trans->x_speed >
		    touched_box->left_edge &&
	    touching_box->top_edge < touched_box->bottom_edge &&
	    touching_box->bottom_edge > touched_box->top_edge) {
		trans->x_speed = 0;
	}

	if (trans->y_speed > 0 &&
	    touching_box->bottom_edge + trans->y_speed >
		    touched_box->top_edge &&
	    touching_box->left_edge < touched_box->right_edge &&
	    touching_box->right_edge > touched_box->left_edge) {
		trans->y_speed = 0;
	}

	if (trans->x_speed < 0 &&
	    touching_box->left_edge + trans->x_speed >
		    touched_box->right_edge &&
	    touching_box->top_edge < touched_box->bottom_edge &&
	    touching_box->bottom_edge > touched_box->top_edge) {
		trans->x_speed = 0;
	}

	if (trans->y_speed < 0 &&
	    touching_box->top_edge + trans->y_speed >
		    touched_box->bottom_edge &&
	    touching_box->left_edge < touched_box->right_edge &&
	    touching_box->right_edge > touched_box->left_edge) {
		trans->y_speed = 0;
	}
}

void physics_system::check_collision_sides(
	ECS::ComponentHandle<struct transform> trans,
	ECS::ComponentHandle<struct box_collider> touching_box,
	sf::RectangleShape touched_rect)
{
	float touched_rect_left = touched_rect.getPosition().x;
	float touched_rect_right =
		touched_rect_left + touched_rect.getGlobalBounds().width;

	float touched_rect_top = touched_rect.getPosition().y;
	float touched_rect_bottom =
		touched_rect_top + touched_rect.getGlobalBounds().height;

	if (trans->x_speed > 0 &&
	    touching_box->right_edge + trans->x_speed > touched_rect_left &&
	    touching_box->top_edge < touched_rect_bottom &&
	    touching_box->bottom_edge > touched_rect_top) {
		trans->x_speed = 0;
	}

	if (trans->y_speed > 0 &&
	    touching_box->bottom_edge + trans->y_speed > touched_rect_top &&
	    touching_box->left_edge < touched_rect_right &&
	    touching_box->right_edge > touched_rect_left) {
		trans->y_speed = 0;
	}

	if (trans->x_speed < 0 &&
	    touching_box->left_edge + trans->x_speed > touched_rect_right &&
	    touching_box->top_edge < touched_rect_bottom &&
	    touching_box->bottom_edge > touched_rect_top) {
		trans->x_speed = 0;
	}

	if (trans->y_speed < 0 &&
	    touching_box->top_edge + trans->y_speed > touched_rect_bottom &&
	    touching_box->left_edge < touched_rect_right &&
	    touching_box->right_edge > touched_rect_left) {
		trans->y_speed = 0;
	}
}

void physics_system::push_entity(ECS::Entity *touching_ent,
				 ECS::Entity *touched_ent)
{
	ECS::ComponentHandle<struct transform> touching_trans =
		touching_ent->get<struct transform>();
	ECS::ComponentHandle<struct transform> touched_trans =
		touched_ent->get<struct transform>();

	if ((touching_trans->x - touched_trans->x_speed) <
	    (touched_trans->x - touching_trans->x_speed)) {
		touched_trans->x++;
	} else if ((touching_trans->x - touched_trans->x_speed) >
		   (touched_trans->x - touching_trans->x_speed)) {
		touched_trans->x--;
	}

	if ((touching_trans->y - touched_trans->y_speed) <
	    (touched_trans->y - touching_trans->y_speed)) {
		touched_trans->y++;
	} else if ((touching_trans->y - touched_trans->y_speed) >
		   (touched_trans->y - touching_trans->y_speed)) {
		touched_trans->y--;
	}
}

void physics_system::tick(ECS::World *world, float delta_time)
{
	if (!states::get_paused()) {
		world->each<struct box_collider, struct sprite_2d,
			    struct transform>(
			[&](ECS::Entity *entity,
			    ECS::ComponentHandle<struct box_collider> box,
			    ECS::ComponentHandle<struct sprite_2d> sprite,
			    ECS::ComponentHandle<struct transform> trans)
				-> void {
				box->update(
					trans->x, trans->y,
					sprite->self.getTextureRect().width,
					sprite->self.getTextureRect().height);
			});

		world->each<
			struct box_collider, struct transform,
			struct tag>([&](ECS::Entity *touching_entity,
					ECS::ComponentHandle<struct box_collider>
						touching_box,
					ECS::ComponentHandle<struct transform>
						trans1,
					ECS::ComponentHandle<struct tag> tag1)
					    -> void {
			world->each<struct box_collider, struct transform,
				    struct tag>(
				[&](ECS::Entity *touched_entity,
				    ECS::ComponentHandle<struct box_collider>
					    touched_box,
				    ECS::ComponentHandle<struct transform>
					    trans2,
				    ECS::ComponentHandle<struct tag> tag1)
					-> void {
					if (touching_entity->getEntityId() !=
					    touched_entity->getEntityId()) {
						if (is_colliding(touching_box,
								 touched_box))
							push_entity(
								touching_entity,
								touched_entity);
					}
				});
		});

		world->each<struct transform>(
			[&](ECS::Entity *entity,
			    ECS::ComponentHandle<struct transform> trans)
				-> void { trans->move(); });
	}
}
