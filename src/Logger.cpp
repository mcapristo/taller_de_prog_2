/*
 * Logger.cpp
 *
 *  Created on: Apr 13, 2015
 *      Author: rha
 */

#include "Logger.h"
#include <stddef.h>
#include <fstream>
#include "Constants.h"
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
			case (Constants::INFO) :
				logFile << "INFO " << " " << message;
				break;
			case (Constants::WARN) :
				logFile << "WARN " << " " << message;
				break;
			case (Constants::ERROR) :
				logFile << "ERROR " << " " << message;
				break;
			case (Constants::DEBUG) :
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
