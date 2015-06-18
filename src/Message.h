/*
 * Message.h
 *
 *  Created on: 10/4/2015
 *      Author: mateo
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <ctime>
#include "User.h"
#include "Loggero.h"
#include "json/json.h"

using namespace std;
using namespace Json;

class Message {
public:
	Message(User* emisor, User* receptor, string body);
	Message(Json::Value);
	virtual ~Message();
	const string& getBody() const;
	string getDatetime() const;
	User* getEmisor();
	User* getReceptor();
	void setReceptor(User* u);
	Value toJsonValue();
	string toJsonString();
	string getId();
	void setId(string id);

private:
	User* emisor;
	User* receptor;
	string datetime;
	string body;
	string id;
};

#endif /* MESSAGE_H_ */
