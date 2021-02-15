#include "interface/button.h"

button::button(void)
{
}

button::~button(void)
{
}

button::button(sf::Vector2f size, sf::Color colour, std::string text)
{
	this->pressed = false;
	this->released = false;
	this->clicked = false;
	this->highlighted = false;

	this->default_colour = sf::Color(color);
	this->highlight_colour = sf::Color(color.r + 50, color.g + 50,
					   color.b + 50, color.a + 50);

	this->background.setSize(size);
	this->background.setFillColor(this->default_colour);
	this->background.setPosition(sf::Vector2f(0, 0));

	this->text.setCharacterSize(12);
	this->text.setFillColor(sf::Color(this->highlight_colour.r * 2,
					  this->highlight_colour.g * 2,
					  this->highlight_colour.b * 2));
	this->text.setPosition(sf::Vector2f(0, 0));
	this->text.setString(text);
}

bool button::highlight(sf::RenderWindow *wnd)
{
	if (this->background.getGlobalBounds().contains(
		    wnd->mapPixelToCoords(sf::Mouse::getPosition(*wnd)))) {
		this->background.setFillColor(this->highlight_colour);
		this->highlighted = true;
	} else {
		this->background.setFillColor(this->default_colour);
		this->highlighted = false;
	}
}

void button::update(sf::Event event, float delta)
{

}

void button::render(sf::RenderWindow *wnd, float delta)
{
	wnd->draw(this->background);
	wnd->draw(this->text);
	wnd->display();
}

void button::check_pressed(sf::Event event)
{
	if (this->highlighted) {
		if (event.type == sf::Event::MouseButtonPressed) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				this->pressed = true;
			} else {
				this->pressed = false;
				this->clicked = false;
			}
		}

		if (this->pressed) {
			if (event.type == sf::Event::MouseButtonReleased) {
				this->released = true;
				this->clicked = true;
			}
		} else {
			this->released = false;
			this->clicked = false;
		}
	}
}
