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
	string validateToken(User* user,string token);

	string createUser(string json);

	string sendMessage(string username, string token, string json);

	string getConversations(string username,string token);

	string getMessages(string username, string token, string user2);

	string getUserProfile(string username, string token, string userToVisit);

	string getUsersProfile(string username, string token);

//	string updateProfile(string username, string token, string data);

	static string ERROR_STRING;
	static string OK_STRING;

	static int INVALID_USERNAME;
	static int INVALID_PASSWORD;
	static int INVALID_TOKEN;
	static int ERROR_SEND_MESSAGE;
	static int ERROR_USER_PROFILE_DOESNT_EXISTS;
	static int NO_USERNAME;
	static int NO_PASSWORD;
	static int USERNAME_ALREADY_EXISTS;
private:
	Database* db;
};

#endif /* SERVICELAYER_H_ */
