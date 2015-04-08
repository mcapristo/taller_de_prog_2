#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include "rocksdb/db.h"

#include "User.h"

using namespace std;
using namespace rocksdb;




int main() {
	std::cout << "!!!Hello World!!!" << std::endl; // prints !!!Hello World!!!
	rocksdb::DB* db;
	rocksdb::Options options;
	options.create_if_missing = true;
	rocksdb::Status status = rocksdb::DB::Open(options, "/tmp/testdb", &db);
	User* u = new User("mateo","pass");
	string u_json = u->toJsonString();
	db->Put(WriteOptions(), "key1", u_json);
	string value;
	db->Get(ReadOptions(),"key1",&value);

	std::cout << value << std::endl;
	delete u;
}

