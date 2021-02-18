#pragma once

#ifndef INTERFACE_BUTTON_MAP_H
#define INTERFACE_BUTTON_MAP_H 1

#include <SFML/Graphics.hpp>

#include "button.h"

class button_map {
public:
	static std::map<std::string, button *> &get_map(void);

private:
	static std::map<std::string, button *> buttons;
};

#endif /* !INTERFACE_BUTTON_MAP_H */
