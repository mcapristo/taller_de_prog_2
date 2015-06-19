/*
 * Clock.h
 *
 *  Created on: 19/6/2015
 *      Author: mateo
 */

#ifndef CLOCK_H_
#define CLOCK_H_

#include <iostream>

using namespace std;

class Clock {
public:
	Clock();
	virtual ~Clock();

	static string getTime();
};

#endif /* CLOCK_H_ */
