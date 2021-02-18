#include "interface/tile.h"

tile::tile(void) {}

tile::~tile(void) {}

tile::tile(float x, float y, float grid_size, bool colliding)
{
	this->area.setSize(sf::Vector2f(grid_size, grid_size));
	this->area.setFillColor(sf::Color::White);
	this->area.setPosition(x * grid_size, y * grid_size);

	this->colliding = colliding;
}

void tile::render(sf::RenderTarget &target)
{
	target.draw(this->area);
}

const bool &tile::get_collision(void) const
{
	return this->colliding;
}

const sf::Vector2f &tile::get_pos(void) const
{
	return this->area.getPosition();
}

std::string tile::to_string(void)
{
	std::stringstream stream;

	stream << this->colliding << " ";

	return stream.str();
}
