/*
 * Message_Test.cpp
 *
 *  Created on: 11/4/2015
 *      Author: mateo
 */

#include "Message.h"
#include <gtest/gtest.h>
#include "User.h"

TEST(MessageTests,TestNewMessage){
	User* u1 = new User("tevez");
	User* u2 = new User("schiavi");
	string body = "hello world";
	Message* m = new Message(u1,u2,body);
	ASSERT_EQ(u1->getUsername(),m->getEmisor()->getUsername());
	ASSERT_EQ(u2->getUsername(),m->getReceptor()->getUsername());
	ASSERT_EQ(body,m->getBody());

	delete u1;
	delete u2;
	delete m;
}

TEST(MessageTests,TestGetSetId){
	User* u1 = new User("tevez");
	User* u2 = new User("schiavi");
	string body = "hello world";
	Message* m = new Message(u1,u2,body);
	string id = "tevezschiavi0";
	m->setId(id);
	ASSERT_EQ(id,m->getId());
	delete u1;
	delete u2;
	delete m;
}

TEST(MessageTests,TestMessageToJsonValueAndNextToMessage){
	User* u1 = new User("tevez");
	User* u2 = new User("schiavi");
	string body = "hello world";
	Message* m = new Message(u1,u2,body);
	string id = "tevezschiavi0";
	m->setId(id);
	Json::Value value = m->toJsonValue();
	Message* m2 = new Message(value);
	ASSERT_EQ(m->getEmisor()->getUsername(),m2->getEmisor()->getUsername());
	ASSERT_EQ(m->getReceptor()->getUsername(),m2->getReceptor()->getUsername());
	ASSERT_EQ(m->getBody(),m2->getBody());
	ASSERT_EQ(m->getId(),m2->getId());
	delete u1;
	delete u2;
	delete m;
	delete m2;
}

TEST(MessageTests, TestMessageSettersAndGetters){
	User u1 = User("tevez");
	User u2 = User("carlo");
	User u3 = User("osvaldo");
	string body = "veni a boca mostro";
	Message m = Message(&u1,&u2,body);
	ASSERT_EQ(u1.getUsername(),m.getEmisor()->getUsername());
	ASSERT_EQ(u2.getUsername(),m.getReceptor()->getUsername());

	m.setReceptor(&u3);
	ASSERT_EQ(u3.getUsername(),m.getReceptor()->getUsername());
	ASSERT_TRUE(m.getDatetime() != "");
}

