#include "systems/render.h"
#include "ecs.h"

render_system::render_system(void)
{

}

render_system::~render_system(void)
{

}

void render_system::tick(ECS::World *world, float delta)
{
	world->each<struct transform, struct sprite_2d>(
			/* Lambda function to be run on each entity */
			[&](ECS::Entity *ent, ECS::ComponentHandle<struct transform> trans, ECS::ComponentHandle<struct sprite_2d> sprite)
			{
				/* Later */
			});
}

