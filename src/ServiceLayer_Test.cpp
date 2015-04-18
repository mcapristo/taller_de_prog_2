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
	ASSERT_EQ(ServiceLayer::ERROR_STRING,valueResponse["result"].asString());
	ASSERT_EQ(ServiceLayer::INVALID_USERNAME,valueResponse["code"].asInt());
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
	ASSERT_EQ(ServiceLayer::ERROR_STRING,valueResponse["result"].asString());
	ASSERT_EQ(ServiceLayer::INVALID_PASSWORD,valueResponse["code"].asInt());
	delete u;
}

TEST(TestsServiceLayer,TestUserValidLogout){
	UserFactory uf = UserFactory();
	string user = "usuario";
	string pass = "contrasenia";
	User* u = uf.createUser(user,pass);
	ServiceLayer sl = ServiceLayer();
	Database* d = sl.getDatabase();
	d->saveUser(u);
	string responseLogin = sl.login(user,pass);
	Json::Value valueResponseLogin = d->getJsonValueFromString(responseLogin);
	string token = valueResponseLogin["token"].asString();
	string responseLogout = sl.logout(user,token);
	Json::Value valueResponseLogout = d->getJsonValueFromString(responseLogout);

	ASSERT_EQ("",valueResponseLogout["token"].asString());
	ASSERT_EQ(false,valueResponseLogout["online"].asBool());

	delete u;
}

TEST(TestsServiceLayer,TestUserInvalidLogoutBecauseOfInvalidUsername){
	UserFactory uf = UserFactory();
	string user = "usuario";
	string pass = "contrasenia";
	User* u = uf.createUser(user,pass);
	ServiceLayer sl = ServiceLayer();
	Database* d = sl.getDatabase();
	d->saveUser(u);
	string responseLogin = sl.login(user,pass);
	Json::Value valueResponseLogin = d->getJsonValueFromString(responseLogin);
	string token = valueResponseLogin["token"].asString();
	string responseLogout = sl.logout(user+"1",token);
	Json::Value valueResponseLogout = d->getJsonValueFromString(responseLogout);

	ASSERT_EQ(ServiceLayer::ERROR_STRING,valueResponseLogout["result"].asString());
	ASSERT_EQ(ServiceLayer::INVALID_USERNAME,valueResponseLogout["code"].asInt());

	delete u;
}

TEST(TestsServiceLayer,TestUserInvalidLogoutBecauseOfInvalidToken){
	UserFactory uf = UserFactory();
	string user = "usuario";
	string pass = "contrasenia";
	User* u = uf.createUser(user,pass);
	ServiceLayer sl = ServiceLayer();
	Database* d = sl.getDatabase();
	d->saveUser(u);
	string responseLogin = sl.login(user,pass);
	Json::Value valueResponseLogin = d->getJsonValueFromString(responseLogin);
	string token = valueResponseLogin["token"].asString();
	string responseLogout = sl.logout(user,token+"1");
	Json::Value valueResponseLogout = d->getJsonValueFromString(responseLogout);

	ASSERT_EQ(ServiceLayer::ERROR_STRING,valueResponseLogout["result"].asString());
	ASSERT_EQ(ServiceLayer::INVALID_TOKEN,valueResponseLogout["code"].asInt());

	delete u;
}

