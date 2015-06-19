/*
 * Loggero.h
 *
 *  Created on: Apr 13, 2015
 *      Author: rha
 */

#ifndef LOGGERO_H_
#define LOGGERO_H_

#include <string.h>
#include <stdlib.h>
#include <iostream>

#include "Constants.h"
#include "Clock.h"

using namespace std;

class Loggero {
public:
	static Loggero* getInstnce();
	virtual ~Loggero();
	int log(int type, string message);
private:
	Loggero();
	static Loggero* instance;
};

#endif /* LOGGERO_H_ */
