/*
 * Proceso.cpp
 *
 *  Created on: 26/4/2015
 *      Author: mateo
 */

#include "Proceso.h"

Proceso::Proceso() {
	SignalHandler :: getInstance()->registrarHandler ( SIGINT,&sigint_handler );
}

Proceso::~Proceso() {
	SignalHandler :: destruir ();
}
