#include "interface/buttom_map.h"

static std::map<std::string, button *> &button_map::get_map(void)
{
	return this->buttons;
}
