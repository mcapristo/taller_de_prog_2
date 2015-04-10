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
#include "json/json.h"

using namespace std;
using namespace Json;

class Message {
public:
	Message(User* emisor, User* receptor, string body);
	virtual ~Message();
	const string& getBody() const;
	time_t getDatetime() const;
	User* getEmisor();
	User* getReceptor();
	Value toJsonValue();
	string toJsonString();
	string getId();
	void setId(string id);

private:
	User* emisor;
	User* receptor;
	time_t datetime;
	string body;
	string id;
};

#endif /* MESSAGE_H_ */
