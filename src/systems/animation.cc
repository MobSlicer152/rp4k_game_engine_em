#include "systems/animation.h"

animation_system::animation_system(void)
{
}
animation_system::~animation_system(void)
{
}

void animation_system::tick(ECS::World *world, float delta_time)
{
	world->each<struct animator, struct sprite_2d>(
		[&](ECS::Entity *entity,
		    ECS::ComponentHandle<struct animator> anim,
		    ECS::ComponentHandle<struct sprite_2d> sprite) -> void {
			anim->current_time += delta_time;

			if (anim->current_time >= anim->next_frame_time) {
				anim->current_time = 0;
				anim->current_column =
					(anim->current_column + 1) %
					anim->total_columns;
			}

			sprite->self.setTextureRect(sf::IntRect(
				anim->current_column * anim->sprite_width,
				anim->current_row * anim->sprite_height,
				anim->sprite_width, anim->sprite_height));
		});
}
