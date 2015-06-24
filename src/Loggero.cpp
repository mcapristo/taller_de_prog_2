/*
 * Logger.cpp
 *
 *  Created on: Apr 13, 2015
 *      Author: rha
 */

#include "Loggero.h"
#include <stddef.h>
#include <fstream>
#include "Constants.h"
Loggero* Loggero::instance = NULL;

/**
 *
 * @return the instance of the singleton Loggero
 */
Loggero* Loggero::getInstnce() {
	if(!instance){
		instance = new Loggero();
	}

	return instance;
}

Loggero::Loggero(){
}

Loggero::~Loggero() {
}

/**
 *
 * @param type of log. See Constants
 * @param message the message to log
 * @return 1 in error, 0 in success
 */
int Loggero::log(int type, string message) {
	ofstream logFile;
	logFile.open ("./log.txt", ios::app);

	if(logFile.is_open()){
		switch (type){
			case (Constants::INFO) :
				logFile << Clock::getTime() << " - " << "INFO - " << message;
				break;
			case (Constants::WARN) :
				logFile << Clock::getTime() << " - " << "WARN - " << message;
				break;
			case (Constants::ERROR) :
				logFile << Clock::getTime() << " - " << "ERROR - " << message;
				break;
			case (Constants::DEBUG) :
				logFile << Clock::getTime() << " - " << "DEBUG - " << message;
				break;
		}

		logFile << "." << "\n";
	}
	else{
		cout << "No se pudo abrir el archivo de log." << endl;
		return 1;
	}

	logFile.close();
	return 0;
}
