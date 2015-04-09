/*
 * Database.cpp
 *
 *  Created on: 8/4/2015
 *      Author: mateo
 */

#include "Database.h"

Database::Database() {
	Options options;
	options.create_if_missing = true;
	Status status = DB::Open(options, "/tmp/testdb", &this->db);
}

Database::~Database() {
	// TODO Auto-generated destructor stub
}

string Database::get(string key) {
	string value;
	Status res = this->db->Get(ReadOptions(),key,&value);
	// TODO: ver si hacer algo con el resultado
	return value;
}

bool Database::put(string key, string value) {
	Status res = db->Put(WriteOptions(), key, value);
	return res.ok();
}

User* Database::getUser(string key) {
	string json = this->get(key);
	Json::Reader r = Json::Reader();
	Json::Value val = Json::Value();
	r.parse(json,val,false);

	User* user = new User(val);
	return user;
}
