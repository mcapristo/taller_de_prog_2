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
	void login();
	Json::Value toJsonValue();
	string toJsonString();

private:
	string username;
	string password;
	string name;
	//UBICACION
	//FOTO DE PERFIL
	bool online;
	string token;
};

#endif /* USER_H_ */
