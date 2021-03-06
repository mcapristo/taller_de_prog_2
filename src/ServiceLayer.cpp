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
int ServiceLayer::ERROR_USER_PROFILE_DOESNT_EXISTS = 5;
int ServiceLayer::USERNAME_ALREADY_EXISTS = 6;
int ServiceLayer::NO_PASSWORD = 7;
int ServiceLayer::NO_USERNAME = 8;
int ServiceLayer::INVALID_JSON = 9;
int ServiceLayer::ERROR_ON_SAVE = 10;

ServiceLayer::ServiceLayer() {
	this->db = new Database();
}

ServiceLayer::~ServiceLayer() {
	delete this->db;
}

Database* ServiceLayer::getDatabase(){
	return this->db;
}

/**
 *
 * @param username
 * @param password
 * @return
 */
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
		value["data"] = u->getUserLoginProfileJsonValue();
	}
	delete u;
	return this->getDatabase()->getJsonStringFromValue(value);
}

/**
 *
 * @param username
 * @param token
 * @return
 */
string ServiceLayer::logout(string username, string token){
	User* u = this->getDatabase()->getUser(username);
	string res = this->isValidToken(u,token);
	if (res != ""){
		delete u;
		return res;
	}
	Json::Value value = Json::Value();
	u->logout();
	this->getDatabase()->saveUser(u);
	Json::Value json = u->getUserProfileJsonValue();
	value["result"] = ServiceLayer::OK_STRING;
	value["data"] = json;
	delete u;
	return this->getDatabase()->getJsonStringFromValue(value);
}

/**
 *
 * @param username
 * @param token
 * @return
 */
string ServiceLayer::validateToken(string username, string token){
	User* u = this->getDatabase()->getUser(username);
	string res = this->isValidToken(u,token);
	if (res == ""){
		Json::Value val = Json::Value();
		val["result"] = ServiceLayer::OK_STRING;
		val["data"] = u->getUserLoginProfileJsonValue();
		delete u;
		return this->getDatabase()->getJsonStringFromValue(val);
	}
	delete u;
	return res;
}

/**
 *
 * @param u
 * @param token
 * @return
 */
string ServiceLayer::isValidToken(User* u, string token){
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
	if (u->getToken() == token){
		u->setLastActivityDatetime(Clock::getTime());
		this->getDatabase()->saveUser(u);
	}
	return "";
}

/**
 *
 * @param json
 * @return
 */
string ServiceLayer::createUser(string json){
	UserFactory uf = UserFactory();
	Json::Value valueToReturn = Json::Value();
	User* createdUser;
	try{
		createdUser = uf.createUserFromJsonString(json);
	}catch(const std::exception&) {
		valueToReturn["result"] = ServiceLayer::ERROR_STRING;
		valueToReturn["code"] = ServiceLayer::INVALID_JSON;
		return this->getDatabase()->getJsonStringFromValue(valueToReturn);
	}

	string username = createdUser->getUsername();
	string pass = createdUser->getPassword();
	if (this->getDatabase()->getUser(createdUser->getUsername()) != NULL){
		valueToReturn["result"] = ServiceLayer::ERROR_STRING;
		valueToReturn["code"] = ServiceLayer::USERNAME_ALREADY_EXISTS;
	}
	else if (username == ""){
		valueToReturn["result"] = ServiceLayer::ERROR_STRING;
		valueToReturn["code"] = ServiceLayer::NO_USERNAME;
	}
	else if (pass == ""){
		valueToReturn["result"] = ServiceLayer::ERROR_STRING;
		valueToReturn["code"] = ServiceLayer::NO_PASSWORD;
	}
	else{
		this->getDatabase()->saveUser(createdUser);
		Json::Value createdUserJson = createdUser->toJsonValue();
		delete createdUser;
		valueToReturn["result"] = ServiceLayer::OK_STRING;
		valueToReturn["data"] = createdUserJson;
	}
	return this->getDatabase()->getJsonStringFromValue(valueToReturn);

}

/**
 *
 * @param username
 * @param token
 * @param data
 * @return
 */
string ServiceLayer::updateProfile(string username, string token, string data){
	User* u = this->getDatabase()->getUser(username);
	string res = this->isValidToken(u,token);
	if (res != ""){
		delete u;
		return res;
	}
	Json::Value input = this->getDatabase()->getJsonValueFromString(data);
	bool resultUpdate = false;
	Json::Value ret = Json::Value();
	try{
		u->updateUser(input);
		resultUpdate = this->db->saveUser(u);
	}
	catch(const std::exception&) {
		resultUpdate = false;
	}
	if (resultUpdate){
		ret["result"] = ServiceLayer::OK_STRING;
		ret["data"] = u->getUserProfileJsonValue();
	}
	else{
		ret["result"] = ServiceLayer::ERROR_STRING;
		ret["code"] = ServiceLayer::ERROR_ON_SAVE;
	}
	delete u;
	return this->getDatabase()->getJsonStringFromValue(ret);
}

/**
 *
 * @param username
 * @param token
 * @param jsonMessage
 * @return
 */
string ServiceLayer::sendMessage(string username, string token, string jsonMessage){
	User* u = this->getDatabase()->getUser(username);
	string res = this->isValidToken(u,token);
	delete u;
	if (res != ""){
		return res;
	}
	Json::Value rootValue = Json::Value();
	Json::Value value = this->getDatabase()->getJsonValueFromString(jsonMessage);
	Message* m = MessageFactory::createMessage(value);
	if (m == NULL){
		rootValue["result"] = ServiceLayer::ERROR_STRING;
		rootValue["code"] = ServiceLayer::INVALID_JSON;
		return db->getJsonStringFromValue(rootValue);
	}
	if (m->getEmisor()->getUsername() != username){
		rootValue["result"] = ServiceLayer::ERROR_STRING;
		rootValue["code"] = ServiceLayer::ERROR_SEND_MESSAGE;
		return db->getJsonStringFromValue(rootValue);
	}
	if (m->getReceptor()->getUsername() == ""){
		return this->sendDiffusionMessage(username, m);
	}
	bool result = this->getDatabase()->saveMessage(m);
	if (result){
		rootValue["result"] = ServiceLayer::OK_STRING;
		rootValue["data"] = m->toJsonValue();
	}
	else{
		rootValue["result"] = ServiceLayer::ERROR_STRING;
		rootValue["code"] = ServiceLayer::ERROR_SEND_MESSAGE;
	}
	delete m;
	return db->getJsonStringFromValue(rootValue);
}

/**
 *
 * @param sender
 * @param m
 * @return
 */
string ServiceLayer::sendDiffusionMessage(string sender, Message* m){
	Json::Value rootValue = Json::Value();
	rootValue["result"] = ServiceLayer::OK_STRING;
	rootValue["data"] = m->toJsonValue();
	vector<User*> users = this->db->getUsers();
	size_t i;
	for (i = 0; i < users.size(); i++){
		User* receptor = users[i];
		if (receptor->getUsername() != sender){
			m->setReceptor(receptor);
			this->db->saveMessage(m);
		}
	}
	return this->db->getJsonStringFromValue(rootValue);
}

/**
 *
 * @param username
 * @param token
 * @return
 */
string ServiceLayer::getConversations(string username, string token){
	User* u = this->getDatabase()->getUser(username);
	string res = this->isValidToken(u,token);
	if (res != ""){
		delete u;
		return res;
	}
	vector<Conversation*> conversations = this->getDatabase()->getConversations(u);
	Json::Value rootValue = Json::Value();
	Json::Value conversationsValue = Json::Value();
	for(size_t i = 0 ; i< conversations.size() ; i++){
		Conversation* c = conversations[i];
		Json::Value conversationJsonValue = c->toJsonValue();
		conversationsValue.append(conversationJsonValue);
		delete c;
	}
	rootValue["result"] = ServiceLayer::OK_STRING;
	rootValue["data"] = conversationsValue;
	delete u;
	return this->getDatabase()->getJsonStringFromValue(rootValue);
}

/**
 *
 * @param username
 * @param token
 * @param user2
 * @return
 */
string ServiceLayer::getMessages(string username, string token, string user2){
	User* u = this->getDatabase()->getUser(username);
	string res = this->isValidToken(u,token);
	if (res != ""){
		delete u;
		return res;
	}
	Json::Value rootValue = Json::Value();
	User* u2 = this->getDatabase()->getUser(user2);
	if (u2 == NULL){
		rootValue["result"] = ServiceLayer::OK_STRING;
		rootValue["data"].append("");
	}
	else{
		Conversation* conv = this->getDatabase()->getConversation(u,u2);
		rootValue["result"] = ServiceLayer::OK_STRING;

		if (conv == NULL) rootValue["data"].append("");
		else rootValue["data"] = this->getDatabase()->getMessagesJsonValue(conv);
	}
	delete u;
	delete u2;
	return this->getDatabase()->getJsonStringFromValue(rootValue);
}

/**
 *
 * @param username
 * @param token
 * @param userToVisit
 * @return
 */
string ServiceLayer::getUserProfile(string username, string token, string userToVisit){
	User* u = this->getDatabase()->getUser(username);
	string res = this->isValidToken(u,token);
	if (res != ""){
		delete u;
		return res;
	}
	Json::Value rootValue = Json::Value();
	User* visited = this->getDatabase()->getUser(userToVisit);
	if ( visited == NULL){
		delete u;
		rootValue["result"] = ServiceLayer::ERROR_STRING;
		rootValue["code"] = ServiceLayer::ERROR_USER_PROFILE_DOESNT_EXISTS;
	}
	else{
		rootValue["result"] = ServiceLayer::OK_STRING;
		rootValue["data"] = visited->getUserProfileJsonValue();
	}
	return this->getDatabase()->getJsonStringFromValue(rootValue);
}

/**
 *
 * @param username
 * @param token
 * @return
 */
string ServiceLayer::getUsersProfile(string username, string token){
	User* u = this->getDatabase()->getUser(username);
	string res = this->isValidToken(u,token);
	if (res != ""){
		delete u;
		return res;
	}
	Json::Value rootValue = Json::Value();
	Json::Value vectorValue = Json::Value();
	vector<User*> users = this->getDatabase()->getUsers();
	for (size_t i = 0; i < users.size() ; i ++){
		User* u = users[i];
		Json::Value userValue = u->getUserProfileJsonValue();
		vectorValue.append(userValue);
	}
	rootValue["result"] = ServiceLayer::OK_STRING;
	rootValue["data"] = vectorValue;
	return this->getDatabase()->getJsonStringFromValue(rootValue);
}
