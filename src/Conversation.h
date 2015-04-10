/*
 * Conversation.h
 *
 *  Created on: 10/4/2015
 *      Author: mateo
 */

#ifndef CONVERSATION_H_
#define CONVERSATION_H_

#include "User.h"

class Conversation {
public:
	Conversation(User* u1, User* u2);
	Conversation(Json::Value value);
	virtual ~Conversation();
	int getTotalMessages();
	void increaseTotalMessages();

private:
	int total_messages;
	User* user1;
	User* user2;
};

#endif /* CONVERSATION_H_ */
