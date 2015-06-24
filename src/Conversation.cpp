/*
 * Conversation.cpp
 *
 *  Created on: 10/4/2015
 *      Author: mateo
 */

#include "Conversation.h"
/**
 *
 * @param u1 One user in the conversation
 * @param u2 The other user in the conversation
 */
Conversation::Conversation(User* u1, User* u2) {
	this->user1 = u1;
	this->user2 = u2;
	this->total_messages = 0;
	this->id = "";
}

/**
 *
 * @param value A Json::Value that represents the conversation
 */
Conversation::Conversation(Json::Value value){
	string u1 = value.get("user1","").asString();
	string u2 = value.get("user2", "").asString();
	string id = value.get("id","").asString();
	int total_messages = value.get("total_messages",0).asInt();
	this->user1 = new User(u1);
	this->user2 = new User(u2);
	this->total_messages = total_messages;
	this->id = id;
}

Conversation::~Conversation() {
}

/**
 *
 * @return total_messages in conversation as int
 */
int Conversation::getTotalMessages(){
	return this->total_messages;
}

/**
 * Increase total_messages by 1
 */
void Conversation::increaseTotalMessages(){
	this->total_messages ++;
}

/**
 *
 * @return One of the users
 */
User* Conversation::getFirstUser(){
	return this->user1;
}

/**
 *
 * @return One of the users
 */
User* Conversation::getSecondUser(){
	return this->user2;
}

/**
 *
 * @return The conversation as a Json::Value
 */
Json::Value Conversation::toJsonValue(){
	Json::Value value(Json::objectValue);
	value["user1"] = this->user1->getUsername();
	value["user2"] = this->user2->getUsername();
	value["total_messages"] = this->total_messages;
	value["id"] = this->id;
	return value;
}

/**
 *
 * @param id : The id of the conversation
 */
void Conversation::setId(string id){
	this->id = id;
}

/**
 *
 * @return The id of the conversation
 */
string Conversation::getId(){
	return this->id;
}

/**
 *
 * @return The conversation as a json string
 */
string Conversation::toJsonString(){
	Json::StreamWriterBuilder builder;
	builder.settings_["identation"] = "\t";
	return Json::writeString(builder,this->toJsonValue());
}
