/*
 * UserFactory.h
 *
 *  Created on: 10/4/2015
 *      Author: mateo
 */

#ifndef USERFACTORY_H_
#define USERFACTORY_H_

#include "User.h"
#include "json/json.h"

using namespace std;

class UserFactory {
public:
	UserFactory();
	virtual ~UserFactory();
	User* createUser(string username, string password);
	User* createUserFromJsonValue(Json::Value value);
	//User* createUserFromJsonString(string json);
};

#endif /* USERFACTORY_H_ */
