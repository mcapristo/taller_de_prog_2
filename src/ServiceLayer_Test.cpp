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
	Json::Value rootValue = d->getJsonValueFromString(response);
	ASSERT_EQ(ServiceLayer::OK_STRING, rootValue["result"].asString());
	Json::Value valueResponse = rootValue["data"];
	ASSERT_NE(valueResponse["token"].asString(), "");
	ASSERT_TRUE(valueResponse["online"].asBool());

	User* userFromDB = sl.getDatabase()->getUser(user);
	ASSERT_EQ(valueResponse["token"].asString(),userFromDB->getToken());
	ASSERT_EQ(true,userFromDB->isOnline());
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
	Json::Value userValue = valueResponseLogin["data"];
	string token = userValue["token"].asString();
	string responseLogout = sl.logout(user,token);
	Json::Value valueResponseLogout = d->getJsonValueFromString(responseLogout);

	ASSERT_EQ("",valueResponseLogout["token"].asString());
	ASSERT_EQ(false,valueResponseLogout["online"].asBool());

	User* userFromDB = sl.getDatabase()->getUser(user);
	ASSERT_EQ(false,userFromDB->isOnline());

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
	string token = valueResponseLogin["data"]["token"].asString();
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
	string token = valueResponseLogin["data"]["token"].asString();
	string responseLogout = sl.logout(user,token+"1");
	Json::Value valueResponseLogout = d->getJsonValueFromString(responseLogout);

	ASSERT_EQ(ServiceLayer::ERROR_STRING,valueResponseLogout["result"].asString());
	ASSERT_EQ(ServiceLayer::INVALID_TOKEN,valueResponseLogout["code"].asInt());

	delete u;
}

TEST(TestsServiceLayer,TestSendValidMessage){
	UserFactory uf = UserFactory();
	string user1 = "emisor";
	string user2 = "receptor";
	string pass = "contrasenia";
	User* u1 = uf.createUser(user1,pass);
	User* u2 = uf.createUser(user2,pass);
	ServiceLayer sl = ServiceLayer();
	Database* d = sl.getDatabase();
	d->saveUser(u1);
	string responseLogin = sl.login(user1,pass);
	Json::Value valueResponseLogin = d->getJsonValueFromString(responseLogin);
	string token = valueResponseLogin["data"]["token"].asString();

	Message* m = new Message(u1,u2,"primer mensaje");

	string responseStringSendMessage = sl.sendMessage(user1,token,m->toJsonString());
	delete m;
	Json::Value responseValueSendMessage = sl.getDatabase()->getJsonValueFromString(responseStringSendMessage);
	ASSERT_EQ(sl.OK_STRING,responseValueSendMessage["result"].asString());
	Json::Value lala = responseValueSendMessage["data"];
	string dataString = sl.getDatabase()->getJsonStringFromValue(lala);
	Json::Value dataJsonValue = sl.getDatabase()->getJsonValueFromString(dataString);
	ASSERT_EQ(user1,dataJsonValue["emisor"].asString());
	ASSERT_EQ(user2,dataJsonValue["receptor"].asString());
	delete u1;
	delete u2;
}

TEST(TestsServiceLayer,TestGetUserConversations){
	UserFactory uf = UserFactory();
	string user1 = "emisor";
	string user2 = "receptor1";
	string user3 = "receptor2";
	string user4 = "receptor3";
	string pass = "contrasenia";
	User* emisor = uf.createUser(user1,pass);
	User* u1 = uf.createUser(user2,pass);
	User* u2 = uf.createUser(user3,pass);
	User* u3 = uf.createUser(user4,pass);
	ServiceLayer sl = ServiceLayer();
	Database* d = sl.getDatabase();
	d->saveUser(emisor);
	d->saveUser(u1);
	d->saveUser(u2);
	d->saveUser(u3);
	string responseLogin = sl.login(user1,pass);
	Json::Value valueResponseLogin = d->getJsonValueFromString(responseLogin);
	string token = valueResponseLogin["data"]["token"].asString();

	Message* m11 = new Message(emisor,u1,"mensaje1 al receptor1");
	Message* m21 = new Message(emisor,u1,"mensaje2 al receptor1");
	Message* m12 = new Message(emisor,u2,"mensaje1 al receptor2");
	Message* m13 = new Message(emisor,u3,"mensaje1 al receptor3");

	sl.sendMessage(user1,token,m11->toJsonString());
	sl.sendMessage(user1,token,m21->toJsonString());
	sl.sendMessage(user1,token,m12->toJsonString());
	sl.sendMessage(user1,token,m13->toJsonString());

	string conversationsJson = sl.getConversations(user1,token);
	Json::Value conversationValue = d->getJsonValueFromString(conversationsJson);
	ASSERT_EQ(ServiceLayer::OK_STRING,conversationValue["result"].asString());
	Json::Value dataValue = conversationValue["data"];
	ASSERT_EQ(3,dataValue.size());

	delete u1;
	delete u2;
	delete u3;
	delete emisor;
	delete m11;
	delete m12;
	delete m13;
	delete m21;
}

TEST(TestsServiceLayer, TestGetMessagesWithTwoUsers){
	UserFactory uf = UserFactory();
	string user1 = "emisor";
	string user2 = "receptor";
	string pass = "contrasenia";
	User* emisor = uf.createUser(user1,pass);
	User* u1 = uf.createUser(user2,pass);
	ServiceLayer sl = ServiceLayer();
	Database* d = sl.getDatabase();
	d->deleteDatabaseValues();
	d->saveUser(emisor);
	d->saveUser(u1);
	string responseLogin = sl.login(user1,pass);
	Json::Value valueResponseLogin = d->getJsonValueFromString(responseLogin);
	string token = valueResponseLogin["data"]["token"].asString();

	string responseLogin2 = sl.login(user2,pass);
	Json::Value valueResponseLogin2 = d->getJsonValueFromString(responseLogin2);
	string token2 = valueResponseLogin2["data"]["token"].asString();

	Message* m1 = new Message(emisor,u1,"mensaje1 al receptor1");
	Message* m2 = new Message(emisor,u1,"mensaje2 al receptor1");
	Message* m3 = new Message(emisor,u1,"mensaje3 al receptor1");
	Message* m4 = new Message(emisor,u1,"mensaje4 al receptor1");

	sl.sendMessage(user1,token,m1->toJsonString());
	sl.sendMessage(user1,token,m2->toJsonString());
	sl.sendMessage(user1,token,m3->toJsonString());
	sl.sendMessage(user1,token,m4->toJsonString());

	string messagesJson = sl.getMessages(user1, token, user2);
	string messagesJson2 = sl.getMessages(user2,token2,user1);

	Json::Value messagesJsonValue1 = sl.getDatabase()->getJsonValueFromString(messagesJson);
	Json::Value messagesJsonValue2 = sl.getDatabase()->getJsonValueFromString(messagesJson2);
	ASSERT_EQ(ServiceLayer::OK_STRING, messagesJsonValue1["result"].asString());
	ASSERT_EQ(4, messagesJsonValue1["data"].size());
	ASSERT_EQ(4, messagesJsonValue2["data"].size());
	ASSERT_TRUE(messagesJsonValue1 == messagesJsonValue2);

	delete m1;
	delete m2;
	delete m3;
	delete m4;
	delete u1;
	delete emisor;
}

TEST(TestsServiceLayer,TestGetOtherUserProfile){
	ServiceLayer sl = ServiceLayer();
	UserFactory uf = UserFactory();
	string username = "carlos01";
	string name = "Carlos";
	string visitorUsername = "visitor";
	string pass = "contrasenia";
	User* u = uf.createUser(username,pass);
	u->setName(name);
	User* visitor = uf.createUser(visitorUsername,pass);
	Database* d = sl.getDatabase();
	d->deleteDatabaseValues();
	d->saveUser(u);
	d->saveUser(visitor);

	string responseLogin = sl.login(visitorUsername,pass);
	Json::Value valueResponseLogin = d->getJsonValueFromString(responseLogin);
	string token = valueResponseLogin["data"]["token"].asString();

	string userJson = sl.getUserProfile(visitorUsername, token, username);
	Json::Value responseValue = sl.getDatabase()->getJsonValueFromString(userJson);
	Json::Value userJsonValue = responseValue["data"];

	ASSERT_EQ(ServiceLayer::OK_STRING, responseValue["result"].asString());
	ASSERT_EQ(name, userJsonValue["name"].asString());
	ASSERT_EQ(username , userJsonValue["username"].asString());
	ASSERT_EQ(false,userJsonValue["online"].asBool());

	sl.login(username,pass);

	userJson = sl.getUserProfile(visitorUsername, token, username);
	responseValue = sl.getDatabase()->getJsonValueFromString(userJson);
	userJsonValue = responseValue["data"];

	ASSERT_EQ(ServiceLayer::OK_STRING, responseValue["result"].asString());
	ASSERT_EQ(name, userJsonValue["name"].asString());
	ASSERT_EQ(username , userJsonValue["username"].asString());
	ASSERT_EQ(true,userJsonValue["online"].asBool());


	delete u;
	delete visitor;
}

TEST(TestsServiceLayer,TestCreateUser){
	ServiceLayer sl = ServiceLayer();
	sl.getDatabase()->deleteDatabaseValues();
	string jsonString = "{\"username\":\"mpalermo\",\"password\":\"contrasenia\",\"name\":\"Martin Palermo\"}";
	string resultString = sl.createUser(jsonString);
	Json::Value resultValue = sl.getDatabase()->getJsonValueFromString(resultString);
	Json::Value userValue = resultValue["data"];
	ASSERT_EQ(ServiceLayer::OK_STRING, resultValue["result"].asString());
	ASSERT_EQ("mpalermo",userValue["username"].asString());
	ASSERT_EQ("contrasenia",userValue["password"].asString());
	ASSERT_EQ("Martin Palermo", userValue["name"].asString());
}

TEST(TestsServiceLayer, TestCreateUserWithUsernameThatAlreadyExists){
	ServiceLayer sl = ServiceLayer();
	sl.getDatabase()->deleteDatabaseValues();
	string jsonString1 = "{\"username\":\"mpalermo\",\"password\":\"contrasenia\",\"name\":\"Martin Palermo\"}";
	sl.createUser(jsonString1);
	string jsonString2 = "{\"username\":\"mpalermo\",\"password\":\"123456\",\"name\":\"Martin Palermo2\"}";
	string resultString2 = sl.createUser(jsonString2);
	Json::Value resultValue2 = sl.getDatabase()->getJsonValueFromString(resultString2);
	ASSERT_EQ(ServiceLayer::ERROR_STRING, resultValue2["result"].asString());
	ASSERT_EQ(ServiceLayer::USERNAME_ALREADY_EXISTS, resultValue2["code"].asInt());
}

TEST(TestsServiceLayer, TestCreateUserWithNoUsername){
	ServiceLayer sl = ServiceLayer();
	sl.getDatabase()->deleteDatabaseValues();
	string jsonString = "{\"username\":\"\",\"password\":\"contrasenia\",\"name\":\"Martin Palermo\"}";
	string resultString = sl.createUser(jsonString);
	Json::Value resultValue = sl.getDatabase()->getJsonValueFromString(resultString);
	ASSERT_EQ(ServiceLayer::ERROR_STRING, resultValue["result"].asString());
	ASSERT_EQ(ServiceLayer::NO_USERNAME, resultValue["code"].asInt());
}

TEST(TestsServiceLayer, TestCreateUserWithNoPassword){
	ServiceLayer sl = ServiceLayer();
	sl.getDatabase()->deleteDatabaseValues();
	string jsonString = "{\"username\":\"mpalermo\",\"password\":\"\",\"name\":\"Martin Palermo\"}";
	string resultString = sl.createUser(jsonString);
	Json::Value resultValue = sl.getDatabase()->getJsonValueFromString(resultString);
	ASSERT_EQ(ServiceLayer::ERROR_STRING, resultValue["result"].asString());
	ASSERT_EQ(ServiceLayer::NO_PASSWORD, resultValue["code"].asInt());
}

TEST(TestsServiceLayer, TestSendMessageWithInvalidJson){
	UserFactory uf = UserFactory();
	string user1 = "emisor";
	string pass = "contrasenia";
	User* u1 = uf.createUser(user1,pass);
	ServiceLayer sl = ServiceLayer();
	Database* d = sl.getDatabase();
	d->saveUser(u1);
	string responseLogin = sl.login(user1,pass);
	Json::Value valueResponseLogin = d->getJsonValueFromString(responseLogin);
	string token = valueResponseLogin["data"]["token"].asString();

	string messageJsonString = "{}";

	string responseStringSendMessage = sl.sendMessage(user1,token,messageJsonString);

	Json::Value responseValueSendMessage = sl.getDatabase()->getJsonValueFromString(responseStringSendMessage);
	ASSERT_EQ(sl.ERROR_STRING,responseValueSendMessage["result"].asString());
	ASSERT_EQ(sl.INVALID_JSON,responseValueSendMessage["code"].asInt());

	delete u1;
}

TEST(TestsServiceLayer, TestSendMessageWithInvalidEmisor){
	UserFactory uf = UserFactory();
	string user1 = "emisor";
	string user3 = "emisor2";
	string user2 = "receptor";
	string pass = "contrasenia";
	User* u1 = uf.createUser(user1,pass);
	User* u2 = uf.createUser(user2,pass);
	User* u3 = uf.createUser(user3,pass);
	ServiceLayer sl = ServiceLayer();
	Database* d = sl.getDatabase();
	d->saveUser(u1);
	string responseLogin = sl.login(user1,pass);
	Json::Value valueResponseLogin = d->getJsonValueFromString(responseLogin);
	string token = valueResponseLogin["data"]["token"].asString();

	Message* m = new Message(u3,u2,"primer mensaje");

	string responseStringSendMessage = sl.sendMessage(user1,token,m->toJsonString());
	delete m;
	Json::Value responseValueSendMessage = sl.getDatabase()->getJsonValueFromString(responseStringSendMessage);
	ASSERT_EQ(sl.ERROR_STRING,responseValueSendMessage["result"].asString());
	ASSERT_EQ(sl.ERROR_SEND_MESSAGE,responseValueSendMessage["code"].asInt());
	delete u1;
	delete u2;
	delete u3;

}

TEST(TestsServiceLayer, TestUpdateUser){
	ServiceLayer sl = ServiceLayer();
	Json::Value val = Json::Value();
	string username = "tevez";
	string password = "messicagon";
	val["username"] = username;
	val["password"] = password;

	sl.createUser(sl.getDatabase()->getJsonStringFromValue(val));
	string responseLogin = sl.login(username, password);
	Json::Value valueResponseLogin = sl.getDatabase()->getJsonValueFromString(responseLogin);
	string token = valueResponseLogin["data"]["token"].asString();

	Json::Value val2 = Json::Value();
	string name = "carlos tevez";
	bool online = true;
	double latitud = 90;
	double longitud = 20;
	string profileImage = "hereshoudbeaimageinhex64asaveryfuckinglongstring";
	string location = "fuerte apache";
	val2["name"] = name;
	val2["online"] = online;
	val2["latitud"] = latitud;
	val2["longitud"] = longitud;
	val2["profileImage"] = profileImage;
	val2["location"] = location;

	string responseUpdate = sl.updateProfile(username, token, sl.getDatabase()->getJsonStringFromValue(val2));
	Json::Value valueResponseUpdate = sl.getDatabase()->getJsonValueFromString(responseUpdate);

	ASSERT_EQ(name, valueResponseUpdate["data"]["name"].asString());
	ASSERT_EQ(online, valueResponseUpdate["data"]["online"].asBool());
	ASSERT_EQ(latitud, valueResponseUpdate["data"]["latitud"].asDouble());
	ASSERT_EQ(longitud, valueResponseUpdate["data"]["longitud"].asDouble());
	ASSERT_EQ(profileImage, valueResponseUpdate["data"]["profileImage"].asString());
	ASSERT_EQ(location, valueResponseUpdate["data"]["location"].asString());


}
