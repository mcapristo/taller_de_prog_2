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
	bool online = value.get("online",false).asBool();
	string token = value.get("token","").asString();
	string profileImage = value.get("profileImage", "").asString();
	double latitud = value.get("latitud", 0).asDouble();
	double longitud = value.get("longitud", 0).asDouble();
	string location = value.get("location","").asString();
	string checkinDatetime = value.get("checkinDatetime","").asString();
	string lastActivityDatetime = value.get("lastActivityDatetime","").asString();

	User* u = new User(username);
	u->setPassword(password);
	u->setName(name);
	u->setOnline(online);
	u->setToken(token);
	u->setProfileImage(profileImage);
	u->setLatitud(latitud);
	u->setLongitud(longitud);
	u->setLocation(location);
	u->setCheckinDatetime(checkinDatetime);
	u->setLastActivityDatetime(lastActivityDatetime);
	return u;
}

User* UserFactory::createUserFromJsonString(string json) {
	Json::Reader r = Json::Reader();
	Json::Value val = Json::Value();
	r.parse(json,val,false);
	return this->createUserFromJsonValue(val);
}
