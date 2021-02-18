#include "interface/button_map.h"

std::map<std::string, button *> button_map::buttons;

std::map<std::string, button *> &button_map::get_map(void)
{
	return buttons;
}
