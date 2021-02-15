#pragma once

#ifndef INTERFACE_STATES_H
#define INTERFACE_STATES_H 1

class states {
public:
	static bool get_paused(void);
	static void set_paused(bool paused);

private:
	static bool paused;
};

#endif /* !INTERFACE_STATES_H */
