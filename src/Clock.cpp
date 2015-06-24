/*
 * Clock.cpp
 *
 *  Created on: 19/6/2015
 *      Author: mateo
 */

#include "Clock.h"

/**
 *
 * @return datetime as a string
 */
string Clock::getTime() {
	time_t now = time(0);
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y/%m/%d %X", &tstruct);

	return buf;
}
