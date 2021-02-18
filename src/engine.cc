#include "engine.h"

engine &engine::get_inst(void)
{
	static engine _inst;
	return _inst;
}

void engine::start(sf::RenderWindow *win)
{
	this->running = true;
	this->win = win;

	while (this->running)
		this->update();
}

void engine::add_system(ECS::EntitySystem *system)
{
	this->world->registerSystem(system);
	this->world->enableSystem(system);
}

void engine::update(void)
{
	sf::Event event;

	if (!this->win->isOpen())
		this->running = false;

	while (this->win->pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			this->win->close();
	}

	this->world->tick(10.0f);

	this->main_cam.update(world, 10.0f, this->win);

	if (states::get_paused())
		paused_actions();
}

engine::engine(void)
{
}

engine::~engine(void)
{
}

void engine::paused_actions(void)
{
	this->pause.render(this->win, 10.0f, main_cam.view.getCenter());
}
