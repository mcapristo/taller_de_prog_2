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

Conversation::Conversation(Json::Value value){
	string u1 = value.get("user1","").asString();
	string u2 = value.get("user2", "").asString();
	int total_messages = value.get("total_messages","").asInt();
	this->user1 = new User(u1);
	this->user2 = new User(u2);
	this->total_messages = total_messages;
}

Conversation::~Conversation() {

}

int Conversation::getTotalMessages(){
	return this->total_messages;
}

void Conversation::increaseTotalMessages(){
	this->total_messages ++;
}
