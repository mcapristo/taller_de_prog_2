/*
 * UserFactory.cpp
 *
 *  Created on: 10/4/2015
 *      Author: mateo
 */

#include "UserFactory.h"

UserFactory::UserFactory() {

}

UserFactory::~UserFactory() {

}

User* UserFactory::createUser(string username, string password){
	User* u = new User(username);
	u->setPassword(password);
	return u;
}

User* UserFactory::createUserFromJsonValue(Json::Value value) {
	string username = value.get("username","").asString();
	string password = value.get("password", "").asString();
	string name = value.get("name", "").asString();
	bool online = value.get("online","0").asString() == "1";
	User* u = new User(username);
	u->setPassword(password);
	u->setName(name);
	u->setOnline(online);
	return u;
}

//User* UserFactory::createUserFromJsonString(string json);
