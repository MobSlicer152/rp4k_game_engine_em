#include "engine.h"

int main(int argc, char *argv[])
{
	engine &inst = engine::get_inst();

	inst.start(new sf::RenderWindow(sf::VideoMode(1024, 600), "RP4K Game Engine"));

	return 0;
}
