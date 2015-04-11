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
	bool res = d.createUser(user);
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
