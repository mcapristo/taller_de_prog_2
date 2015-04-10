/*
 * Conversation.cpp
 *
 *  Created on: 10/4/2015
 *      Author: mateo
 */

#include "Conversation.h"

Conversation::Conversation(User* u1, User* u2) {
	this->user1 = u1;
	this->user2 = u2;
	this->total_messages = 0;
}

Conversation::~Conversation() {

}

