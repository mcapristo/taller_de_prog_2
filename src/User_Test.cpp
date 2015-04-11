#include "User.h"
#include "json/json.h"
#include <gtest/gtest.h>

TEST(UserTests,TestUserCreation){
	string username = "mpalermo";
	User* user = new User(username);
	string password = "password";
	user->setPassword(password);
	string name = "Martin Palermo";
	user->setName(name);
	user->setOnline(true);
	ASSERT_EQ(username,user->getUsername());
	ASSERT_EQ(password,user->getPassword());
	ASSERT_EQ(name, user->getName());
	ASSERT_EQ(true, user->isOnline());
	delete user;
}

TEST(UserTests,TestUserToJsonValue){
	User* u = new User("mpalermo");
	u->setPassword("contrasenia");
	u->setName("Martin Palermo");
	u->setOnline(true);
	Json::Value value = u->toJsonValue();
	string username = value.get("username","").asString();
	string password = value.get("password", "").asString();
	string name = value.get("name", "").asString();
	bool online = value.get("online","0").asString() == "1";
	ASSERT_EQ("mpalermo", username);
	ASSERT_EQ("contrasenia",password);
	ASSERT_EQ("Martin Palermo", name);
	ASSERT_EQ(true, online);
	delete u;
}
