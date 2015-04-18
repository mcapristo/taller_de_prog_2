/*
 * Database.h
 *
 *  Created on: 8/4/2015
 *      Author: mateo
 */

#ifndef DATABASE_H_
#define DATABASE_H_

#include "rocksdb/db.h"
#include "rocksdb/slice.h"
#include "rocksdb/options.h"

#include "UserFactory.h"
#include "Message.h"
#include "Conversation.h"

using namespace rocksdb;
using namespace std;

class Database {
public:
	Database();
	virtual ~Database();

	string get(ColumnFamilyHandle* cfHandle,string key);
	bool put(ColumnFamilyHandle* cfHandle, string key, string value);

	string get(string key);
	bool put(string key, string value);

	User* getUser(string key);
	bool saveUser(User* user);

	Message* getMessage(string id);
	bool saveMessage(Message* m);

	int deleteDatabaseValues();
	Json::Value getJsonValueFromString(string str);

	Conversation* getConversation(User* u1, User* u2);
	bool saveConversation(Conversation* conv);

	string getUsersJsonString();
	Json::Value getUsersJsonValue();

	string getMessagesJsonString(Conversation* conv);
	Json::Value getMessagesJsonValue(Conversation* conv);

private:
	DB* db;
	ColumnFamilyHandle* defaultCF;
	ColumnFamilyHandle* userCF;
	ColumnFamilyHandle* conversationCF;
	ColumnFamilyHandle* messageCF;
	bool saveMessageWithKey(Message* m, string key);


};

#endif /* DATABASE_H_ */
