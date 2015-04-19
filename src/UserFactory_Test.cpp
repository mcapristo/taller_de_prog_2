#include "UserFactory.h"
#include <gtest/gtest.h>

TEST(UserFactoryTest,TestUserFactoryFromStringJson){
	string json = "{\"username\":\"mpalermo\",\"password\":\"contrasenia\",\"name\":\"Martin Palermo\",\"online\":true}";
	UserFactory uf = UserFactory();
	User* user = uf.createUserFromJsonString(json);
	ASSERT_EQ("mpalermo",user->getUsername());
	ASSERT_EQ("contrasenia",user->getPassword());
	ASSERT_EQ("Martin Palermo", user->getName());
	ASSERT_EQ(true, user->isOnline());
	delete user;
}

TEST(UserFactoryTest,TestUserFactoryUsernameAndPassword){
	string username = "mpalermo";
	string password = "contrasenia";
	UserFactory uf = UserFactory();
	User* u = uf.createUser(username,password);
	ASSERT_EQ(username,u->getUsername());
	ASSERT_EQ(password,u->getPassword());
	delete u;
}
