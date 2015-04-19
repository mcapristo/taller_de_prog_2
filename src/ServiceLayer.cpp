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
int ServiceLayer::ERROR_SEND_MESSAGE = 4;

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
	Json::Value value = Json::Value();
	if (u == NULL){
		value["result"] = ServiceLayer::ERROR_STRING;
		value["code"] = ServiceLayer::INVALID_USERNAME;
	}
	else if (u->getPassword() != password){
		value["result"] = ServiceLayer::ERROR_STRING;
		value["code"] = ServiceLayer::INVALID_PASSWORD;
	}
	else {
		u->login();
		this->db->saveUser(u);
		value["result"] = ServiceLayer::OK_STRING;
		value["data"] = u->toJsonValue();
	}
	delete u;
	return this->getDatabase()->getJsonStringFromValue(value);
}

string ServiceLayer::logout(string username, string token){
	User* u = this->getDatabase()->getUser(username);
	string res = this->validateToken(u,token);
	if (res != ""){
		delete u;
		return res;
	}
	Json::Value value = Json::Value();
	u->logout();
	this->getDatabase()->saveUser(u);
	Json::Value json = u->toJsonValue();
	value["data"] = json;
	delete u;
	return this->getDatabase()->getJsonStringFromValue(value);
}

string ServiceLayer::validateToken(User* u, string token){
	Json::Value value = Json::Value();
	if (u == NULL){
		value["result"] = ServiceLayer::ERROR_STRING;
		value["code"] = ServiceLayer::INVALID_USERNAME;
		return this->getDatabase()->getJsonStringFromValue(value);
	}
	if (u->getToken() != token){
		value["result"] = ServiceLayer::ERROR_STRING;
		value["code"] = ServiceLayer::INVALID_TOKEN;
		return this->getDatabase()->getJsonStringFromValue(value);
	}
	return "";
}

string ServiceLayer::sendMessage(string username, string token, string jsonMessage){
	User* u = this->getDatabase()->getUser(username);
	string res = this->validateToken(u,token);
	delete u;
	if (res != ""){
		return res;
	}
	Json::Value rootValue = Json::Value();
	Json::Value value = this->getDatabase()->getJsonValueFromString(jsonMessage);
	Message* m = new Message(value);
	bool result = this->getDatabase()->saveMessage(m);
	if (result){
		rootValue["result"] = ServiceLayer::OK_STRING;
		rootValue["data"] = m->toJsonString();
	}
	else{
		rootValue["result"] = ServiceLayer::ERROR_STRING;
		rootValue["code"] = ServiceLayer::ERROR_SEND_MESSAGE;
	}
	delete m;
	return db->getJsonStringFromValue(rootValue);
}

string ServiceLayer::getConversations(string username, string token){
	User* u = this->getDatabase()->getUser(username);
	string res = this->validateToken(u,token);
	if (res != ""){
		delete u;
		return res;
	}
	Json::Value value = Json::Value();
	vector<Conversation*> conversations = this->getDatabase()->getConversations(u);
	Json::Value rootValue = Json::Value();
	Json::Value conversationsValue = Json::Value();
	for(size_t i = 0 ; i< conversations.size() ; i++){
		Conversation* c = conversations[i];
		string conversationJsonString = c->toJsonString();
		conversationsValue.append(conversationJsonString);
		delete c;
	}
	rootValue["result"] = ServiceLayer::OK_STRING;
	rootValue["data"] = conversationsValue;
	delete u;
	return this->getDatabase()->getJsonStringFromValue(rootValue);
}
