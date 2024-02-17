#ifndef HELP_H
#define HELP_H

#include <iostream>
#include <assert.h>

#define P(x) std::cout << x << std::endl

double monotime(){
	timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return ts.tv_sec * 1e9 + ts.tv_nsec;
}

#endif

