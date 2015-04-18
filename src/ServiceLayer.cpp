/*
 * ServiceLayer.cpp
 *
 *  Created on: 17/4/2015
 *      Author: mateo
 */

#include "ServiceLayer.h"

ServiceLayer::ServiceLayer() {
	this->db = new Database();
}

ServiceLayer::~ServiceLayer() {
	delete this->db;
}

string ServiceLayer::login(string username, string password){
	User* u = this->db->getUser(username);
	if (u == NULL) return "{\"result\":\"ERROR\",\"code\":1}";
	if (u->getPassword() != password) return "{\"result\":\"ERROR\",\"code\":2}";
	u->login();
	this->db->saveUser(u);
	return u->toJsonString();

}

Database* ServiceLayer::getDatabase(){
	return this->db;
}
