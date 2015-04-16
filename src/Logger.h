/*
 * Logger.h
 *
 *  Created on: Apr 13, 2015
 *      Author: rha
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <string.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

class Logger {
public:
	static Logger* getInstnce();
	virtual ~Logger();
	int log(int type, string message);
private:
	Logger();
	static Logger* instance;
};

#endif /* LOGGER_H_ */
