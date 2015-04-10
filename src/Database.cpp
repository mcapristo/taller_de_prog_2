/*
 * Database.cpp
 *
 *  Created on: 8/4/2015
 *      Author: mateo
 */

#include "Database.h"

Database::Database() {
	Options options;
	options.create_if_missing = true;
	Status status = DB::Open(options, "/tmp/testdb", &this->db);
}

Database::~Database() {

}

string Database::get(string key) {
	string value;
	Status res = this->db->Get(ReadOptions(),key,&value);
	// TODO: ver si hacer algo con el resultado
	return value;
}

bool Database::put(string key, string value) {
	Status res = db->Put(WriteOptions(), key, value);
	return res.ok();
}

Json::Value* Database::getJsonValueFromString(string str) {
	Json::Reader r = Json::Reader();
	Json::Value* val = new Json::Value();
	r.parse(str,*val,false);
	return val;
}

User* Database::getUser(string key) {
	string json = this->get(key);
	if (json == "") return NULL; //TODO: hacer un manejo de errores
	Json::Value* val = this->getJsonValueFromString(json);

	UserFactory uf = UserFactory();
	User* u = uf.createUserFromJsonValue(*val);
	delete val;
	return u;
}

bool Database::createUser(User* user) {
	string username = user->getName();
	string json = user->toJsonString();
	return this->put(username,json);
}


Message* Database::getMessage(string id){
	string json = this->get(id);
	Json::Reader r = Json::Reader();
	Json::Value val = Json::Value();
	r.parse(json,val,false);
	return new Message(val);
}

bool Database::saveMessageWithKey(Message* m, string key){

	string conversationJson = this->get(key);
	Conversation* conv;
	if (conversationJson == ""){
		conv = new Conversation(m->getEmisor(),m->getReceptor());
	}
	else {
		Json::Reader r = Json::Reader();
		Json::Value val = Json::Value();
		r.parse(conversationJson,val,false);
		conv = new Conversation(val);
	}
	int tot_msg = conv->getTotalMessages();
	conv->increaseTotalMessages();
	std::stringstream out;
	out << tot_msg;
	string finalkey = key + out.str();
	//this->saveConversation(conv); TODO para que sobreescriba el tot_msg
	delete conv;

	m->setId(finalkey);
	return this->put(finalkey,m->toJsonString());

}

bool Database::saveMessage(Message* m) {
	string key1 = m->getEmisor()->getUsername() + m->getReceptor()->getUsername();
	string res1 = this->get(key1);

	if (res1 != ""){
		return this->saveMessageWithKey(m,key1);
	}
	else{
		string key2 =  m->getReceptor()->getUsername() + m->getEmisor()->getUsername();
		return this->saveMessageWithKey(m,key2);
	}

}
