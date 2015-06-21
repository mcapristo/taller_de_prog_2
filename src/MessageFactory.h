/*
 * MessageFactory.h
 *
 *  Created on: 17/5/2015
 *      Author: mateo
 */

#ifndef MESSAGEFACTORY_H_
#define MESSAGEFACTORY_H_

#include "json/json.h"

#include "Message.h"

class MessageFactory {
public:
	static Message* createMessage(Json::Value value);
};

#endif /* MESSAGEFACTORY_H_ */
