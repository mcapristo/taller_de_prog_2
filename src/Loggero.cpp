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

string Loggero::getTime() {
	time_t now = time(0);
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y/%m/%d %X", &tstruct);

	return buf;
}

int Loggero::log(int type, string message) {
	ofstream logFile;
	logFile.open ("./log.txt", ios::app);

	if(logFile.is_open()){
		switch (type){
			case (Constants::INFO) :
				logFile << this->getTime() << " - " << "INFO - " << message;
				break;
			case (Constants::WARN) :
				logFile << this->getTime() << " - " << "WARN - " << message;
				break;
			case (Constants::ERROR) :
				logFile << this->getTime() << " - " << "ERROR - " << message;
				break;
			case (Constants::DEBUG) :
				logFile << this->getTime() << " - " << "DEBUG - " << message;
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
