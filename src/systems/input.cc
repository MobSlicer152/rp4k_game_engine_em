#include "systems/input.h"

input_system::input_system(sf::RenderWindow *win)
{
	this->win = win;
}

input_system::~input_system(void)
{
}

void input_system::tick(ECS::World *world, float delta)
{
	get_key_events(world);
}

void input_system::get_key_events(ECS::World *world)
{
	if (!states::get_paused()) {
		world->each<struct input_controller>(
			[&](ECS::Entity *entity,
			    ECS::ComponentHandle<struct input_controller> input)
				-> void {
				input->w = sf::Keyboard::isKeyPressed(
					sf::Keyboard::W);
				input->a = sf::Keyboard::isKeyPressed(
					sf::Keyboard::A);
				input->s = sf::Keyboard::isKeyPressed(
					sf::Keyboard::S);
				input->d = sf::Keyboard::isKeyPressed(
					sf::Keyboard::D);
			});
	}
}
