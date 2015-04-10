#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include "rocksdb/db.h"
#include "json/json.h"

#include "User.h"
#include "Database.h"
#include "Message.h"

using namespace std;
using namespace rocksdb;




int main() {
/*
	std::cout << "!!!Hello World!!!" << std::endl; // prints !!!Hello World!!!
	Database* db = new Database();
	User* u = new User("mateo");
	string userJson = u->toJsonString();

	db->put("clave",userJson);
	User* u2 = db->getUser("clavequenoexiste");




	std::cout << userJson << std::endl;
	std::cout << u2->toJsonString() << std::endl;
*/

	Database* db = new Database();

	User* u1 = new User("mateo");
	User* u2 = new User("carlos");

	Message* m = new Message(u1,u2,"hola mundo");
	string json = m->toJsonString();
	std::cout << "antes de guardar en la base" << std::endl;
	std::cout << json << std::endl;

	db->saveMessage(m);
	string json2 = m->toJsonString();
	std::cout << "despues de guardar en la base" << std::endl;
	std::cout << json2 << std::endl;

	Message* m2 = db->getMessage(m->getId());
	std::cout << "lo que se guardo en la base" << std::endl;
	std::cout << m2->toJsonString() << std::endl;

	delete u1;
	delete u2;
	delete m;
	delete m2;
}

