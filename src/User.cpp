/*
 * User.cpp
 *
 *  Created on: 8/4/2015
 *      Author: mateo
 */

#include "User.h"

/**
 *
 * @param username of the user as a string
 */
User::User(string username) {
	this->username = username;
	this->online = false;
	this->token = "";
	this->profileImage = "";
	this->latitud = 0;
	this->longitud = 0;
	this->location = "";
	this->checkinDatetime = "";
	this->lastActivityDatetime = Clock::getTime();
}

User::~User() {
}

/**
 *
 * @return a string with the name of the user
 */
string User::getName(){
	return name;
}

/**
 *
 * @param name a string with the name of the user
 */
void User::setName(const string& name) {
	this->name = name;
}
/**
 *
 * @return a bool that says if the user is online
 */
bool User::isOnline(){
	return online;
}

/**
 *
 * @param online a bool that says if the user is online
 */
void User::setOnline(bool online) {
	this->online = online;
}

/**
 *
 * @return the password of the user as string
 */
string User::getPassword(){
	return password;
}

/**
 *
 * @param password a string with the password of the user
 */
void User::setPassword(const string& password) {
	this->password = password;
}

/**
 *
 * @return a string with the username
 */
string User::getUsername(){
	return username;
}

/**
 *
 * @return a string with the token of the user.
 */
string User::getToken(){
	return this->token;
}

/**
 *
 * @param t the token of the user as a string
 */
void User::setToken(string t){
	this->token = t;
}

/**
 *
 * @return a string of the profile image encoded
 */
string User::getProfileImage(){
	return this->profileImage;
}

/**
 *
 * @param image a string of the profile image encoded
 */
void User::setProfileImage(string image){
	this->profileImage = image;
}

/**
 *
 * @param latitud a double
 */
void User::setLatitud(double latitud){
	this->latitud = latitud;
}

/**
 *
 * @return a double
 */
double User::getLatitud(){
	return this->latitud;
}

/**
 *
 * @param longitud a double
 */
void User::setLongitud(double longitud){
	this->longitud = longitud;
}

/**
 *
 * @return a double
 */
double User::getLongitud(){
	return this->longitud;
}

/**
 *
 * @param location as a string
 * also change the checkindatetime
 */
void User::setLocation(string location){
	this->location = location;
	this->setCheckinDatetime(Clock::getTime());
}

/**
 *
 * @return a string with the location
 */
string User::getLocation(){
	return this->location;
}

/**
 *
 * @param datetime as a string
 */
void User::setCheckinDatetime(string datetime){
	this->checkinDatetime = datetime;
}

/**
 *
 * @return a string
 */
string User::getCheckinDatetime(){
	return this->checkinDatetime;
}

/**
 *
 * @param datetime as a string
 */
void User::setLastActivityDatetime(string datetime){
	this->lastActivityDatetime = datetime;
}

/**
 *
 * @return a string
 */
string User::getLastActivityDatetime(){
	return this->lastActivityDatetime;
}

/**
 *
 * @return a Json::Value that represents the user
 */
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
	value["location"] = this->location;
	value["checkinDatetime"] = this->checkinDatetime;
	value["lastActivityDatetime"] = this->lastActivityDatetime;

	return value;
}

/**
 *
 * @return a json string that represents the user
 */
string User::toJsonString() {
	Json::StreamWriterBuilder builder;
	builder.settings_["identation"] = "\t";
	return Json::writeString(builder,this->toJsonValue());
}

/**
 * sets the token and the online to true
 */
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

/**
 * deletes the token and sets the online to false
 */
void User::logout(){
	this->setToken("");
	this->online = false;
}

/**
 *
 * @return a Json::Value with the attributes of the user but not the password or the token
 */
Json::Value User::getUserProfileJsonValue(){
	Json::Value val = Json::Value();
	val["username"] = this->getUsername();
	val["name"] = this->getName();
	val["online"] = this->isOnline();
	val["latitud"] = this->getLatitud();
	val["longitud"] = this->getLongitud();
	val["profileImage"] = this->getProfileImage();
	val["location"] = this->getLocation();
	val["checkinDatetime"] = this->getCheckinDatetime();
	val["lastActivityDatetime"] = this->getLastActivityDatetime();
	return val;
}

/**
 *
 * @return a Json::Value with all the attributes of the user but not the password
 */
Json::Value User::getUserLoginProfileJsonValue(){
	Json::Value val = this->getUserProfileJsonValue();
	val["token"] = this->getToken();
	return val;
}

/**
 *
 * @param val Json::Value with the attributes to change to this user.
 * only the following attributes can be changed
 * name, profileImage, password, online, latitud, longitud, location, checkinDatetime, lastActivityDatetime
 */
void User::updateUser(Json::Value val){
	string name = val.get("name","").asString();
	if (name != "") this->setName(name);

	string profileImage = val.get("profileImage", "").asString();
	if (profileImage != "") this->setProfileImage(profileImage);

	string password = val.get("password", "").asString();
	if (password != "") this->setPassword(password);

	bool online = val.get("online", false).asBool();
	this->setOnline(online);

	double latitud = val.get("latitud", 0).asDouble();
	if (latitud != 0) this->setLatitud(latitud);

	double longitud = val.get("longitud", 0).asDouble();
	if (longitud != 0) this->setLongitud(longitud);

	string location = val.get("location","").asString();
	if (location != "") this->setLocation(location);

	string checkinDatetime = val.get("checkinDatetime","").asString();
	if (checkinDatetime != "") this->setCheckinDatetime(checkinDatetime);

	string lastActivityDatetime = val.get("lastActivityDatetime","").asString();
	if (lastActivityDatetime != "") this->setLastActivityDatetime(lastActivityDatetime);
}
