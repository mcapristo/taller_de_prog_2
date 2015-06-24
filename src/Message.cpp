/*
 * Message.cpp
 *
 *  Created on: 10/4/2015
 *      Author: mateo
 */

#include "Message.h"

/**
 *
 * @param emisor a pointer to the user that sends the message
 * @param receptor a pointer to the user that receives the message
 * @param body string.
 */
Message::Message(User* emisor, User* receptor, string body) {
	this->emisor = emisor;
	this->receptor = receptor;
	this->body = body;
	this->datetime = Clock::getTime();
}

/**
 *
 * @param value a Json::Value that represents the message
 */
Message::Message(Json::Value value){
	string emisor = value.get("emisor","").asString();
	string receptor = value.get("receptor", "").asString();
	string id = value.get("id", "").asString();
	string body = value.get("body","").asString();
	string datetime = value.get("datetime","").asString();
	this->emisor = new User(emisor);
	this->receptor = new User(receptor);
	this->body = body;
	this->id = id;
	this->datetime = datetime;
}

Message::~Message() {

}

/**
 *
 * @return the body of the message as string
 */
const string& Message::getBody() const {
	return body;
}

/**
 *
 * @return the datetime of the message as string
 */
string Message::getDatetime() const {
	return datetime;
}

/**
 *
 * @return a pointer to the user that sends the message
 */
User* Message::getEmisor(){
	return this->emisor;
}

/**
 *
 * @return a pointer to the user that receives the message
 */
User* Message::getReceptor() {
	return this->receptor;
}

/**
 *
 * @param u a pointer to the user that receives the message
 */
void Message::setReceptor(User* u){
	this->receptor = u;
}

/**
 *
 * @param id a string that is the id of the message
 */
void Message::setId(string id) {
	this->id = id;
}

/**
 *
 * @return a string that is the id of the message
 */
string Message::getId() {
	return this->id;
}

/**
 *
 * @return a Json::Value of the message
 */
Value Message::toJsonValue() {
	Value value(Json::objectValue);
	value["emisor"] = this->emisor->getUsername();
	value["receptor"] = this->receptor->getUsername();
	value["body"] = this->body;
	value["id"] = this->id;
	value["datetime"] = this->datetime;
	return value;
}

/**
 *
 * @return a json string of the message
 */
string Message::toJsonString() {
	Json::StreamWriterBuilder builder;
	builder.settings_["identation"] = "\t";
	return Json::writeString(builder,this->toJsonValue());
}
