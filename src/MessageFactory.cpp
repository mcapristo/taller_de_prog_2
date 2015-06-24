/*
 * MessageFactory.cpp
 *
 *  Created on: 17/5/2015
 *      Author: mateo
 */

#include "MessageFactory.h"

/**
 *
 * @param value a Json::Value that represents the message
 * @return a pointer to the message
 */
Message* MessageFactory::createMessage(Json::Value value){
	string emisor = value.get("emisor","").asString();
	string receptor = value.get("receptor", "").asString();
	string id = value.get("id", "").asString();
	string body = value.get("body","").asString();
	if (emisor == "" || body == ""){
		return NULL;
	}
	Message* m = new Message(new User(emisor), new User(receptor),body);
	m->setId(id);
	return m;
}
