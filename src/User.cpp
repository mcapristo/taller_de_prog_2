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
	this->profileImage = "";
	this->latitud = 0;
	this->longitud = 0;
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

string User::getProfileImage(){
	return this->profileImage;
}

void User::setProfileImage(string image){
	this->profileImage = image;
}

void User::setLatitud(double latitud){
	this->latitud = latitud;
}

double User::getLatitud(){
	return this->latitud;
}

void User::setLongitud(double longitud){
	this->longitud = longitud;
}

double User::getLongitud(){
	return this->longitud;
}

Json::Value User::toJsonValue() {
	Json::Value value(Json::objectValue);
	value["username"] = this->username;
	value["password"] = this->password;
	value["name"] = this->name;
	value["online"] = this->online;
	value["token"] = this->token;
	value["latitud"] = this->latitud;
	value["longitud"] = this->longitud;
	value["profileImage"] = this->profileImage;

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
	val["latitud"] = this->getLatitud();
	val["longitud"] = this->getLongitud();
	val["profileImage"] = this->getProfileImage();
	return val;
}

Json::Value User::getUserLoginProfileJsonValue(){
	Json::Value val = this->getUserProfileJsonValue();
	val["token"] = this->getToken();
	return val;
}

void User::updateUser(Json::Value val){
	string name = val.get("name","").asString();
	if (name != "") this->setName(name);

	string profileImage = val.get("profileImage", "").asString();
	if (profileImage != "") this->setProfileImage(profileImage);

	string password = val.get("password", "").asString();
	if (password != "") this->setPassword(password);

	double latitud = val.get("latitud", 0).asDouble();
	if (latitud != 0) this->setLatitud(latitud);

	double longitud = val.get("longitud", 0).asDouble();
	if (longitud != 0) this->setLongitud(longitud);
}
