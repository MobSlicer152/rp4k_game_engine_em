#include "engine.h"

int main(int argc, char *argv[])
{
	/* Get the engine instance */
	engine &inst = engine::get_inst();

	/* Create our world for entities */
	inst.world = ECS::World::createWorld();

	/* Create some entities */
	ECS::Entity *background;
	ECS::Entity *test;

	/* Add a system to the engine */
	inst.add_system(new render_system());

	/* Set up the entities */
	background = inst.world->create();
	test = inst.world->create();

	background->assign<struct transform>(0, 0);
	background->assign<struct sprite_2d>("res/textures/background.png");

	test->assign<struct transform>(10, 10);
	test->assign<struct sprite_2d>("res/textures/test_sheet.png");
	test->assign<struct animator>(32, 32, 200.0f, 4, 1);

	/* Print our entity IDs */
	printf("Entity ID of entity \'background\' is %lu\n", background->getEntityId());
	printf("Entity ID of entity \'test\' is %lu\n", test->getEntityId());

	/* Start up the engine */
	inst.start(new sf::RenderWindow(sf::VideoMode(1024, 600), "RP4K Game Engine"));

	return 0;
}
