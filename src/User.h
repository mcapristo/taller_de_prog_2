/*
 * User.h
 *
 *  Created on: 8/4/2015
 *      Author: mateo
 */

#ifndef USER_H_
#define USER_H_

#include <iostream>
#include <bits/functional_hash.h>
#include "json/json.h"

using namespace std;


class User {
public:
	User(string username);
	virtual ~User();
	string getName();
	void setName(const string& name);
	bool isOnline();
	void setOnline(bool online);
	string getPassword();
	void setPassword(const string& password);
	string getUsername();
	void setUsername(const string& username);
	string getToken();
	void setToken(string t);
	string getProfileImage();
	void setProfileImage(string image);
	double getLatitud();
	void setLatitud(double latitud);
	double getLongitud();
	void setLongitud(double longitud);

	void login();
	void logout();
	void updateUser(Json::Value val);
	Json::Value toJsonValue();
	string toJsonString();
	Json::Value getUserProfileJsonValue();

private:
	string username;
	string password;
	string name;
	string profileImage;
	bool online;
	string token;
	double latitud;
	double longitud;
};

#endif /* USER_H_ */
