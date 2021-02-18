#include "interface/main_camera.h"

main_camera::main_camera(void) {}

main_camera::main_camera(sf::Vector2f pivot)
{
	view.setCenter(pivot);
}

main_camera::~main_camera(void) {}

void main_camera::update(ECS::World *world, float delta, sf::RenderWindow *wnd)
{
	sf::Vector2f wnd_size(wnd->getSize().x, wnd->getSize().y);

	view.setSize(wnd_size);

	float move_speed = 0.1f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		this->view.move(-move_speed * delta, 0);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		this->view.move(move_speed * delta, 0);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		this->view.move(0, -move_speed * delta);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		this->view.move(0, move_speed * delta);

	wnd->setView(this->view);
}
