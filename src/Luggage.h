

#define MAX_LUGGAGE 10
#define LUGGAGE_NAME "L"

#pragma once

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "luggage_belts.h"


class Luggage
{
public:
    Luggage(){};
    // ~Luggage(){};
    struct coord {
        int x;
        int y;
    } dot;

	void set_name(const char* text);
    char* get_name();
    bool enable {0};
    float distanse {0};
	int belts_num {-1};
    long int start {0};
private:
    char _name[3];
};