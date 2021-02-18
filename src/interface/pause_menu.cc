#include "interface/pause_menu.h"

pause_menu::pause_menu(void)
{
}

pause_menu::~pause_menu(void)
{
}

pause_menu::pause_menu(sf::RenderWindow *wnd)
{
	states::set_paused(false);
	this->init_buttons(wnd);
}

void pause_menu::update(sf::Event event, float delta, sf::RenderWindow *wnd)
{
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Escape)
			states::set_paused(!states::get_paused());
	}

	button_map::get_map()["RESUME"]->update(event, delta);
	button_map::get_map()["SAVE"]->update(event, delta);
	button_map::get_map()["LOAD"]->update(event, delta);
	button_map::get_map()["QUIT"]->update(event, delta);

	if (button_map::get_map()["RESUME"]->clicked) {
		states::set_paused(!states::get_paused());
		button_map::get_map()["RESUME"]->clicked = false;
	}

	if (button_map::get_map()["QUIT"]->clicked) {
		quit(wnd);
		button_map::get_map()["QUIT"]->clicked = false;
	}
}

void pause_menu::render(sf::RenderWindow *wnd, float delta, sf::Vector2f resume_pos)
{
	sf::Font font;
	font.loadFromFile("res/fonts/cascadia.ttf");

	sf::Vector2f size_offset = sf::Vector2f(button_map::get_map()["RESUME"]->background.getSize().x / 2,
					        button_map::get_map()["RESUME"]->background.getSize().y / 2);

	button_map::get_map()["RESUME"]->background.setPosition(
		resume_pos + sf::Vector2f(0, -80) - size_offset);
	button_map::get_map()["RESUME"]->text.setFont(font);
	button_map::get_map()["RESUME"]->text.setPosition(
		button_map::get_map()["RESUME"]->background.getPosition());
	button_map::get_map()["RESUME"]->highlight(wnd);
	button_map::get_map()["RESUME"]->render(wnd, delta);

	button_map::get_map()["SAVE"]->background.setPosition(
		resume_pos + sf::Vector2f(0, -80) - size_offset);
	button_map::get_map()["SAVE"]->text.setFont(font);
	button_map::get_map()["SAVE"]->text.setPosition(
		button_map::get_map()["SAVE"]->background.getPosition());
	button_map::get_map()["SAVE"]->highlight(wnd);
	button_map::get_map()["SAVE"]->render(wnd, delta);

	button_map::get_map()["LOAD"]->background.setPosition(resume_pos + sf::Vector2f(0, -80) - size_offset);
	button_map::get_map()["LOAD"]->text.setFont(font);
	button_map::get_map()["LOAD"]->text.setPosition(button_map::get_map()["QUIT"]->background.getPosition());
	button_map::get_map()["LOAD"]->highlight(wnd);
	button_map::get_map()["LOAD"]->render(wnd, delta);

	button_map::get_map()["QUIT"]->background.setPosition(resume_pos + sf::Vector2f(0, -80) - size_offset);
	button_map::get_map()["QUIT"]->text.setFont(font);
	button_map::get_map()["QUIT"]->text.setPosition(button_map::get_map()["QUIT"]->background.getPosition());
	button_map::get_map()["QUIT"]->highlight(wnd);
	button_map::get_map()["QUIT"]->render(wnd, delta);

	wnd->display();
}

void pause_menu::init_buttons(sf::RenderWindow *wnd)
{
	int i;

	sf::Vector2f size(wnd->getSize().x, wnd->getSize().y);

	button_map::get_map().insert(
		{ "RESUME",
		  new button(size, sf::Color(255, 135, 0, 255), "Resume") });
	button_map::get_map().insert(
		{ "SAVE",
		  new button(size, sf::Color(255, 135, 0, 255), "Save") });
	button_map::get_map().insert(
		{ "LOAD",
		  new button(size, sf::Color(255, 135, 0, 255), "Load") });
	button_map::get_map().insert(
		{ "QUIT",
		  new button(size, sf::Color(255, 135, 0, 255), "Quit") });
}

void pause_menu::quit(sf::RenderWindow *wnd)
{
	wnd->close();
}
