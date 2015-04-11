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
}


User::~User() {
	// TODO Auto-generated destructor stub
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

Json::Value User::toJsonValue() {
	Json::Value value(Json::objectValue);
	value["username"] = this->username;
	value["password"] = this->password; // La contrasenia no se deberia mandar
	// deberia ser if(this->name == nullptr) pero no compila
	/*if (this->name != "") value["name"] = this->name;
	else value["name"] = "";*/
	value["name"] = this->name;

	if (this->online) value["online"] = "1";//TODO: podria ir el token
	else value["name"] = "0";

	return value;
}

string User::toJsonString() {
	Json::StreamWriterBuilder builder;
	builder.settings_["identation"] = "\t";
	return Json::writeString(builder,this->toJsonValue());

}
