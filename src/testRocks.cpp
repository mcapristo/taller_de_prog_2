#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include "rocksdb/db.h"
#include "json/json.h"

#include "User.h"
#include "Database.h"

using namespace std;
using namespace rocksdb;




int main() {
	std::cout << "!!!Hello World!!!" << std::endl; // prints !!!Hello World!!!
	Database* db = new Database();
	User* u = new User("mateo","pass");
	string userJson = u->toJsonString();

	db->put("clave",userJson);
	User* u2 = db->getUser("clave");




	std::cout << userJson << std::endl;
	std::cout << u2->toJsonString() << std::endl;
	delete u;
}

