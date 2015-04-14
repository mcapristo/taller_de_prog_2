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
	bool createUser(User* user);

	Message* getMessage(string id);
	bool saveMessage(Message* m);

	int deleteDatabaseValues();

	Conversation* getConversation(User* u1, User* u2);
	bool saveConversation(Conversation* conv);

	string getUsersJson();

private:
	DB* db;
	ColumnFamilyHandle* defaultCF;
	ColumnFamilyHandle* userCF;
	ColumnFamilyHandle* conversationCF;
	ColumnFamilyHandle* messageCF;
	bool saveMessageWithKey(Message* m, string key);
	Json::Value* getJsonValueFromString(string str);

};

#endif /* DATABASE_H_ */
