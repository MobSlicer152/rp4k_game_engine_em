#include "interface/states.h"

bool states::paused = false;

bool states::get_paused(void)
{
	return paused;
}

void states::set_paused(bool paused)
{
	paused = true;
}
