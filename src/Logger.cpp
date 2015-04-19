/*
 * Logger.cpp
 *
 *  Created on: Apr 13, 2015
 *      Author: rha
 */

#include "Logger.h"
#include <stddef.h>
#include <fstream>
Logger* Logger::instance = NULL;

Logger* Logger::getInstnce() {
	if(!instance){
		instance = new Logger();
	}

	return instance;
}

Logger::Logger(){
}

Logger::~Logger() {
}

int Logger::log(int type, string message) {
	ofstream logFile;
	logFile.open ("./log.txt", ios::app);

	if(logFile.is_open()){
		switch (type){
			case 1://info
				logFile << "INFO " << " " << message;
				break;
			case 2://warn
				logFile << "WARN " << " " << message;
				break;
			case 3://error
				logFile << "ERROR " << " " << message;
				break;
			case 4://debug
				logFile << "DEBUG " << " " << message;
				break;
		}
		logFile << "\n";
	}
	else{
		cout << "No se pudo abrir el archivo de log";
		return 1;
	}

	logFile.close();
	return 0;
}
