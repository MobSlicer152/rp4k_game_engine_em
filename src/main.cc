#include "engine.h"

int main(int argc, char *argv[])
{
	/* Get the engine instance */
	engine &inst = engine::get_inst();

	/* Create a window */
	sf::RenderWindow *win = new sf::RenderWindow(sf::VideoMode(1024, 600),
						     "RP4K Game Engine");

	/* Create our world for entities */
	inst.world = ECS::World::createWorld();

	/* Create some entities */
	ECS::Entity *background;
	ECS::Entity *test;

	/* Add systems to the engine */
	inst.add_system(new animation_system());
	inst.add_system(new input_system(win));
	inst.add_system(new movement_system());
	inst.add_system(new render_system());
	inst.add_system(new tilemap_system());

	/* Set up the entities */
	background = inst.world->create();
	test = inst.world->create();

	background->assign<struct transform>(0, 0);
	background->assign<struct sprite_2d>("res/textures/background.png");
	background->assign<struct tag>();
	background->get<struct tag>()->add("Background");
	background->assign<struct tilemap>();

	test->assign<struct transform>(100, 10);
	test->assign<struct sprite_2d>("res/textures/test_sheet.png");
	test->assign<struct animator>(32, 32, 200.0f, 4, 1);
	test->get<struct animator>()->current_row = 0; /* idle animation */
	test->assign<struct input_controller>();
	test->assign<struct box_collider>();
	test->assign<main_camera>(sf::Vector2f(win->getSize().x / 2, win->getSize().y / 2));

	/* Print our entity IDs */
	printf("Entity ID of entity \'background\' is %zu\n",
	       background->getEntityId());
	printf("Entity ID of entity \'test\' is %zu\n", test->getEntityId());

	/* Start up the engine */
	inst.start(win);

	return 0;
}
