/*
 * Conversation_Test.cpp
 *
 *  Created on: 11/4/2015
 *      Author: mateo
 */

#include "Conversation.h"
#include <gtest/gtest.h>

TEST(ConversationTests,TestNewConversation){
	User u1 = User("schiavi");
	User u2 = User("guillermo");
	Conversation c = Conversation(&u1,&u2);
	ASSERT_EQ(c.getTotalMessages(),0);
}

TEST(ConversationTests,TestIncreaseTotalMessagesConversation){
	User u1 = User("schiavi");
	User u2 = User("guillermo");
	Conversation c = Conversation(&u1,&u2);
	c.increaseTotalMessages();
	c.increaseTotalMessages();
	ASSERT_EQ(c.getTotalMessages(),2);
}
