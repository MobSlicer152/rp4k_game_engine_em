#include "systems/movement.h"

movement_system::movement_system(void)
{
}

movement_system::~movement_system(void)
{
}

void movement_system::tick(ECS::World *world, float delta)
{
	world->each<struct animator, struct input_controller, struct transform>(
		[&](ECS::Entity *entity,
		    ECS::ComponentHandle<struct animator> anim,
		    ECS::ComponentHandle<struct input_controller> input,
		    ECS::ComponentHandle<struct transform> trans) {
			if (input->input_active) {
				if (input->w) {
					trans->y_speed = -Y_SPEED;
					trans->move();
				} else if (input->s) {
					trans->y_speed = Y_SPEED;
					trans->move();
				} else {
					trans->y_speed = 0;
				}

				if (input->a) {
					anim->facing_right = false;
					anim->current_row = 0;

					trans->x_speed = -X_SPEED;
					trans->move();
				} else if (input->d) {
					anim->facing_right = true;
					anim->current_row = 0;

					trans->x_speed = X_SPEED;
					trans->move();
				} else {
					trans->x_speed = 0;
				}
			}
		});
}
