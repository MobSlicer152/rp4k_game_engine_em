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

void engine::update()
{
	sf::Event event;

	if (!this->win->isOpen())
		this->running = false;

	while (this->win->pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			win->close();
			
		if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
			win->close();
	}
}

engine::engine(void) {}

engine::~engine(void) {}

