/*
 * Database.h
 *
 *  Created on: 8/4/2015
 *      Author: mateo
 */

#ifndef DATABASE_H_
#define DATABASE_H_

#include "rocksdb/db.h"
#include "User.h"

using namespace rocksdb;
using namespace std;

class Database {
public:
	Database();
	virtual ~Database();

	string get(string key);
	bool put(string key, string value);

	User* getUser(string key);

private:
	DB* db;
};

#endif /* DATABASE_H_ */
