/*
 * ServiceLayer.h
 *
 *  Created on: 17/4/2015
 *      Author: mateo
 */

#ifndef SERVICELAYER_H_
#define SERVICELAYER_H_

#include "Database.h"

class ServiceLayer {
public:
	ServiceLayer();
	virtual ~ServiceLayer();

	Database* getDatabase();

	string login(string username, string password);
	string logout(string username, string token);

	string sendMessage(string username, string token, string json);

	static string ERROR_STRING;
	static string OK_STRING;

	static int INVALID_USERNAME;
	static int INVALID_PASSWORD;
	static int INVALID_TOKEN;
	static int ERROR_SEND_MESSAGE;
private:
	Database* db;
};

#endif /* SERVICELAYER_H_ */
