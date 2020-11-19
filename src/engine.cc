#include "engine.h"

engine &engine::create_inst(void)
{
	static engine _inst;
	return _inst;
}
