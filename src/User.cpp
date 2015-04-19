/*
 * User.cpp
 *
 *  Created on: 8/4/2015
 *      Author: mateo
 */

#include "User.h"

User::User(string username) {
	this->username = username;
	this->online = false;
	this->token = "";
}

User::~User() {
}

inline bool operator==(User u1,User u2){
	return (u1.getUsername() == u2.getUsername());
}

string User::getName(){
	return name;
}

void User::setName(const string& name) {
	this->name = name;
}

bool User::isOnline(){
	return online;
}

void User::setOnline(bool online) {
	this->online = online;
}

string User::getPassword(){
	return password;
}

void User::setPassword(const string& password) {
	this->password = password;
}

string User::getUsername(){
	return username;
}

void User::setUsername(const string& username) {
	this->username = username;
}

string User::getToken(){
	return this->token;
}

void User::setToken(string t){
	this->token = t;
}

Json::Value User::toJsonValue() {
	Json::Value value(Json::objectValue);
	value["username"] = this->username;
	value["password"] = this->password; // La contrasenia no se deberia mandar
	value["name"] = this->name;
	value["online"] = this->online;
	value["token"] = this->token;

	return value;
}

string User::toJsonString() {
	Json::StreamWriterBuilder builder;
	builder.settings_["identation"] = "\t";
	return Json::writeString(builder,this->toJsonValue());
}

void User::login(){
	string input = this->getUsername()+this->getPassword()+this->getName();
	std::hash<std::string> hash_fn;
	size_t str_hash = hash_fn(input);
	stringstream ss;
	ss << str_hash;
	string token = ss.str();
	this->setToken(token);
	this->online = true;
}

void User::logout(){
	this->setToken("");
	this->online = false;
}

Json::Value User::getUserProfileJsonValue(){
	Json::Value val = Json::Value();
	val["username"] = this->getUsername();
	val["name"] = this->getName();
	val["online"] = this->isOnline();
	return val;
}

