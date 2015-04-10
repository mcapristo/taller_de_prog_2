/*
 * Message.cpp
 *
 *  Created on: 10/4/2015
 *      Author: mateo
 */

#include "Message.h"

Message::Message(User* emisor, User* receptor, string body) {
	this->emisor = emisor;
	this->receptor = receptor;
	this->body = body;
	this->datetime = time(0);
}

Message::Message(Json::Value value){
	string emisor = value.get("emisor","").asString();
	string receptor = value.get("receptor", "").asString();
	string id = value.get("id", "").asString();
	string body = value.get("body","").asString();
	//string datetime = value.get("datetime","").asString();
	this->emisor = new User(emisor);
	this->receptor = new User(receptor);
	this->body = body;
	this->id = id;
	this->datetime = time(0);
}

Message::~Message() {

}

const string& Message::getBody() const {
	return body;
}

time_t Message::getDatetime() const {
	return datetime;
}

User* Message::getEmisor(){
	return this->emisor;
}

User* Message::getReceptor() {
	return this->receptor;
}

void Message::setId(string id) {
	this->id = id;
}

string Message::getId() {
	return this->id;
}

Value Message::toJsonValue() {
	Value value(Json::objectValue);
	value["emisor"] = this->emisor->getUsername();
	value["receptor"] = this->receptor->getUsername();
	value["body"] = this->body;
	value["id"] = this->id;
	//value["datetime"] = this->datetime; TODO: ver como formatear a string
	return value;
}

string Message::toJsonString() {
	Json::StreamWriterBuilder builder;
	builder.settings_["identation"] = "\t";
	return Json::writeString(builder,this->toJsonValue());
}
