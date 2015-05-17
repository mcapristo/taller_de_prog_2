/*
 * MessageFactory.cpp
 *
 *  Created on: 17/5/2015
 *      Author: mateo
 */

#include "MessageFactory.h"

MessageFactory::MessageFactory() {
	// TODO Auto-generated constructor stub

}

MessageFactory::~MessageFactory() {
	// TODO Auto-generated destructor stub
}

Message* MessageFactory::createMessage(Json::Value value){
	string emisor = value.get("emisor","").asString();
	string receptor = value.get("receptor", "").asString();
	string id = value.get("id", "").asString();
	string body = value.get("body","").asString();
	//string datetime = value.get("datetime","").asString();
	if (emisor == "" || receptor == "" || body == ""){
		return NULL;
	}
	Message* m = new Message(new User(emisor), new User(receptor),body);
	m->setId(id);
	return m;
}
