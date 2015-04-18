/*
 * Message_Test.cpp
 *
 *  Created on: 17/4/2015
 *      Author: mateo
 */

#include "ServiceLayer.h"
#include <gtest/gtest.h>

TEST(TestsServiceLayer,TestUserValidLogin){
	UserFactory uf = UserFactory();
	string user = "usuario";
	string pass = "contrasenia";
	User* u = uf.createUser(user,pass);
	ServiceLayer sl = ServiceLayer();
	Database* d = sl.getDatabase();
	d->saveUser(u);
	string response = sl.login(user,pass);
	Json::Value valueResponse = d->getJsonValueFromString(response);
	ASSERT_NE(valueResponse["token"].asString(), "");
	ASSERT_TRUE(valueResponse["online"].asBool());
	delete u;
}

TEST(TestsServiceLayer,TestUserInvalidLoginBecauseOfInvalidUsername){
	UserFactory uf = UserFactory();
	string user = "usuario";
	string pass = "contrasenia";
	User* u = uf.createUser(user,pass);
	ServiceLayer sl = ServiceLayer();
	Database* d = sl.getDatabase();
	d->deleteDatabaseValues();
	string response = sl.login(user,pass);
	Json::Value valueResponse = d->getJsonValueFromString(response);
	ASSERT_EQ("ERROR",valueResponse["result"].asString());
	ASSERT_EQ("1",valueResponse["code"].asString());
	delete u;
}

TEST(TestsServiceLayer,TestUserInvalidLoginBecauseOfInvalidPassword){
	UserFactory uf = UserFactory();
	string user = "usuario";
	string pass = "contrasenia";
	User* u = uf.createUser(user,pass);
	ServiceLayer sl = ServiceLayer();
	sl.getDatabase()->saveUser(u);
	string response = sl.login(user,pass+"4");
	Json::Value valueResponse = sl.getDatabase()->getJsonValueFromString(response);
	ASSERT_EQ("ERROR",valueResponse["result"].asString());
	ASSERT_EQ("2",valueResponse["code"].asString());
	delete u;
}
