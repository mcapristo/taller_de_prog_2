/*
 * Database_Test.cpp
 *
 *  Created on: 11/4/2015
 *      Author: mateo
 */

#include <gtest/gtest.h>
#include "Database.h"

TEST(TestsDatabase,TestPutAndGetStringFromDatabase){
	Database d = Database();
	string key = "clave";
	string value = "valor";
	bool res = d.put(key,value);
	ASSERT_EQ(true, res);
	string valueFromDatabase = d.get(key);
	ASSERT_EQ(value,valueFromDatabase);
}

TEST(TestsDatabase,TestPutAndGetUserFromDatabase){
	Database d = Database();
	UserFactory uf = UserFactory();
	string json = "{\"username\":\"mpalermo\",\"password\":\"contrasenia\",\"name\":\"Martin Palermo\",\"online\":\"1\"}";
	User* user = uf.createUserFromJsonString(json);
	bool res = d.saveUser(user);
	ASSERT_EQ(true,res);
	User* userFromDatabase = d.getUser("mpalermo");
	ASSERT_EQ(user->getName(),userFromDatabase->getName());
	ASSERT_EQ(user->getUsername(), userFromDatabase->getUsername());
	ASSERT_EQ(user->getPassword(),userFromDatabase->getPassword());

	delete user;
	delete userFromDatabase;
}

TEST(TestsDatabase,TestPutAndGetMessageFromDatabase){
	Database d = Database();
	User u1 = User("cordoba");
	User u2 = User("chicho");
	Message m = Message(&u1,&u2,"first message");
	bool res = d.saveMessage(&m);
	ASSERT_EQ(true,res);
	string new_id = m.getId();
	Message* m2 = d.getMessage(new_id);
	ASSERT_EQ(m.getEmisor()->getUsername(),m2->getEmisor()->getUsername());
	ASSERT_EQ(m.getReceptor()->getUsername(),m2->getReceptor()->getUsername());
	ASSERT_EQ(m.getBody(),m2->getBody());
	ASSERT_EQ(m.getId(),m2->getId());
	delete m2;
}

TEST(TestsDatabase,TestDeleteDatabase){
	Database* d = new Database();
	int res = d->deleteDatabaseValues();
	d->put("a","b");
	res = d->deleteDatabaseValues();
	ASSERT_EQ(1,res);
	delete d;
}

TEST(TestsDatabase,TestPut3Messages){
	Database* d = new Database();
	d->deleteDatabaseValues();
	User u1 = User("user1");
	User u2 = User("user2");
	Message* m1 = new Message(&u1,&u2,"test message1");
	Message* m2 = new Message(&u1,&u2,"test message2");
	Message* m3 = new Message(&u1,&u2,"test message3");
	d->saveMessage(m1);
	d->saveMessage(m2);
	d->saveMessage(m3);
	Conversation* c = d->getConversation(&u1,&u2);
	ASSERT_EQ(3,c->getTotalMessages());
	delete m1;
	delete m2;
	delete m3;
	delete d;
}


TEST(TestsDatabase,TestGetUsersJsonString){
	Database* d = new Database();
	d->deleteDatabaseValues();
	User u1 = User("user1");
	User u2 = User("user2");
	User u3 = User("user3");
	User u4 = User("user4");
	vector<User*> usersFromTest;
	usersFromTest.push_back(&u1);
	usersFromTest.push_back(&u2);
	usersFromTest.push_back(&u3);
	usersFromTest.push_back(&u4);
	d->saveUser(&u1);
	d->saveUser(&u2);
	d->saveUser(&u3);
	d->saveUser(&u4);
	string usersJson = d->getUsersJsonString();
	Json::Reader r = Json::Reader();
	Json::Value val = Json::Value();
	r.parse(usersJson,val,false);
	vector<User> usersFromDB;
	for (Json::Value::iterator it = val["users"].begin(); it != val["users"].end(); ++it) {
		string username = ((*it)["username"].asString());
		User u = User(username);
		usersFromDB.push_back(u);
	}
	vector<string> founds;
	for (size_t i = 0 ; i < usersFromTest.size() ; i++){
		string userFromTest = usersFromTest[i]->getUsername();
		for (size_t j = 0 ; j < usersFromDB.size() ; j++){
			string userFromDB = usersFromDB[j].getUsername();
			if (userFromTest == userFromDB){
				founds.push_back(userFromDB);
			}
		}
	}
	ASSERT_EQ(4,founds.size());
	delete d;
}

TEST(TestsDatabase,TestGetMessagesJsonString){
	Database* d = new Database();
	d->deleteDatabaseValues();
	User u1 = User("user1");
	User u2 = User("user2");
	Message* m1 = new Message(&u1,&u2,"test message1");
	Message* m2 = new Message(&u1,&u2,"test message2");
	Message* m3 = new Message(&u1,&u2,"test message3");
	d->saveMessage(m1);
	d->saveMessage(m2);
	d->saveMessage(m3);
	Conversation* c = d->getConversation(&u1,&u2);
	ASSERT_EQ(3,c->getTotalMessages());
	string json = d->getMessagesJsonString(c);
	delete m1;
	delete m2;
	delete m3;
	delete d;
}

TEST(TestsDatabase,TestUserValidLogin){
	UserFactory uf = UserFactory();
	string user = "usuario";
	string pass = "contrasenia";
	User* u = uf.createUser(user,pass);
	Database d = Database();
	d.saveUser(u);
	string response = d.login(user,pass);
	Json::Value valueResponse = d.getJsonValueFromString(response);
	ASSERT_NE(valueResponse["token"].asString(), "");
	ASSERT_TRUE(valueResponse["online"].asBool());
	delete u;
}

TEST(TestsDatabase,TestUserInvalidLoginBecauseOfInvalidUsername){
	UserFactory uf = UserFactory();
	string user = "usuario";
	string pass = "contrasenia";
	User* u = uf.createUser(user,pass);
	Database d = Database();
	d.deleteDatabaseValues();
	string response = d.login(user,pass);
	cout<<response<<endl;
	Json::Value valueResponse = d.getJsonValueFromString(response);
	ASSERT_EQ("ERROR",valueResponse["result"].asString());
	ASSERT_EQ("1",valueResponse["code"].asString());
	delete u;
}

TEST(TestsDatabase,TestUserInvalidLoginBecauseOfInvalidPassword){
	UserFactory uf = UserFactory();
	string user = "usuario";
	string pass = "contrasenia";
	User* u = uf.createUser(user,pass);
	Database d = Database();
	d.saveUser(u);
	string response = d.login(user,pass+"4");
	Json::Value valueResponse = d.getJsonValueFromString(response);
	ASSERT_EQ("ERROR",valueResponse["result"].asString());
	ASSERT_EQ("2",valueResponse["code"].asString());
	delete u;
}
