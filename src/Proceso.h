/*
 * Proceso.h
 *
 *  Created on: 26/4/2015
 *      Author: mateo
 */

#ifndef PROCESO_H_
#define PROCESO_H_

#include <sys/prctl.h>
#include <iostream>

#include "SIGINT_Handler.h"
#include "SignalHandler.h"

class Proceso {
public:
	Proceso();
	virtual ~Proceso();
	SIGINT_Handler sigint_handler;

};

#endif /* PROCESO_H_ */
