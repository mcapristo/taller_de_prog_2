/*
 * ServiceLayer.cpp
 *
 *  Created on: 17/4/2015
 *      Author: mateo
 */

#include "ServiceLayer.h"

string ServiceLayer::ERROR_STRING = "ERROR";
string ServiceLayer::OK_STRING = "OK";

int ServiceLayer::INVALID_USERNAME = 1;
int ServiceLayer::INVALID_PASSWORD = 2;
int ServiceLayer::INVALID_TOKEN = 3;

ServiceLayer::ServiceLayer() {
	this->db = new Database();
}

ServiceLayer::~ServiceLayer() {
	delete this->db;
}

Database* ServiceLayer::getDatabase(){
	return this->db;
}

string ServiceLayer::login(string username, string password){
	User* u = this->db->getUser(username);
	if (u == NULL) return "{\"result\":\"ERROR\",\"code\":1}";
	if (u->getPassword() != password) return "{\"result\":\"ERROR\",\"code\":2}";
	u->login();
	this->db->saveUser(u);
	string json = u->toJsonString();
	delete u;
	return json;
}

string ServiceLayer::logout(string username, string token){
	User* u = this->getDatabase()->getUser(username);
	Json::Value value = Json::Value();
	if (u == NULL){
		value["result"] = ServiceLayer::ERROR_STRING;
		value["code"] = ServiceLayer::INVALID_USERNAME;
		delete u;
		return this->getDatabase()->getJsonStringFromValue(value);
	}
	if (u->getToken() != token){
		value["result"] = ServiceLayer::ERROR_STRING;
		value["code"] = ServiceLayer::INVALID_TOKEN;
		delete u;
		return this->getDatabase()->getJsonStringFromValue(value);
	}
	u->logout();
	this->getDatabase()->saveUser(u);
	Json::Value json = u->toJsonValue();
	delete u;
	value["data"] = json;
	return this->getDatabase()->getJsonStringFromValue(value);

}
