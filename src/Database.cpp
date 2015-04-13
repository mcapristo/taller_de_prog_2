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
	Status s = DB::Open(options, "/tmp/testdb", &this->db);
	if (s.ok()){
		s = db->CreateColumnFamily(ColumnFamilyOptions(), "UserCF", &this->userCF);
		assert(s.ok());

		s = db->CreateColumnFamily(ColumnFamilyOptions(), "ConversationCF", &this->conversationCF);
		assert(s.ok());

		s = db->CreateColumnFamily(ColumnFamilyOptions(), "MessageCF", &this->messageCF);
		assert(s.ok());
	}
	else {
		std::vector<ColumnFamilyDescriptor> column_families;
		column_families.push_back(ColumnFamilyDescriptor(kDefaultColumnFamilyName,ColumnFamilyOptions()));
		column_families.push_back(ColumnFamilyDescriptor("UserCF",ColumnFamilyOptions()));
		column_families.push_back(ColumnFamilyDescriptor("ConversationCF",ColumnFamilyOptions()));
		column_families.push_back(ColumnFamilyDescriptor("MessageCF",ColumnFamilyOptions()));
		std::vector<ColumnFamilyHandle*> handles;
		Status status = DB::Open(options, "/tmp/testdb",column_families,&handles,&this->db);
		this->defaultCF = handles[0];
		this->userCF = handles[1];
		this->conversationCF = handles[2];
		this->messageCF = handles[3];
	}
}

Database::~Database() {
	delete this->defaultCF;
	delete this->userCF;
	delete this->conversationCF;
	delete this->messageCF;
	delete this->db;
}

string Database::get(string key) {
	return this->get(this->defaultCF,key);
}

bool Database::put(string key, string value) {
	return this->put(this->defaultCF,key,value);
}

string Database::get(ColumnFamilyHandle* cfHandle, string key) {
	string value;
	Status res = this->db->Get(ReadOptions(),cfHandle,key,&value);
	// TODO: ver si hacer algo con el resultado
//	cout<< "GET :clave: '" + key + "', valor: '" + value +"'"<< endl;
	return value;
}

bool Database::put(ColumnFamilyHandle* cfHandle,string key, string value) {
//	cout<< "SET: clave: '" + key + "', valor: '" + value +"'" << endl;
	Status res = db->Put(WriteOptions(),cfHandle, key, value);
	return res.ok();
}

Json::Value* Database::getJsonValueFromString(string str) {
	Json::Reader r = Json::Reader();
	Json::Value* val = new Json::Value();
	r.parse(str,*val,false);
	return val;
}

User* Database::getUser(string key) {
	string json = this->get(this->userCF,key);
	if (json == "") return NULL; //TODO: hacer un manejo de errores
	Json::Value* val = this->getJsonValueFromString(json);

	UserFactory uf = UserFactory();
	User* u = uf.createUserFromJsonValue(*val);
	delete val;
	return u;
}

bool Database::createUser(User* user) {
	string username = user->getUsername();
	string json = user->toJsonString();
	return this->put(this->userCF,username,json);
}


Message* Database::getMessage(string id){
	string json = this->get(this->messageCF,id);
	Json::Reader r = Json::Reader();
	Json::Value val = Json::Value();
	r.parse(json,val,false);
	return new Message(val);
}

bool Database::saveMessageWithKey(Message* m, string key){

	string conversationJson = this->get(this->conversationCF,key);
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
	this->saveConversation(conv);
	delete conv;

	m->setId(finalkey);
	return this->put(this->messageCF,finalkey,m->toJsonString());

}

bool Database::saveMessage(Message* m) {
	string key1 = m->getEmisor()->getUsername() + m->getReceptor()->getUsername();
	string res1 = this->get(this->conversationCF,key1);

	if (res1 != ""){
		return this->saveMessageWithKey(m,key1);
	}
	else{
		string key2 =  m->getReceptor()->getUsername() + m->getEmisor()->getUsername();
		return this->saveMessageWithKey(m,key2);
	}

}

int Database::deleteDatabaseValues(){
	//TODO MODIFICAR PARA COLUMN FAMILIES
	Iterator* it = this->db->NewIterator(ReadOptions());
	it->SeekToFirst();
	int i = 0;
	while (it->Valid()){
		Slice key = it->key();
		this->db->Delete(WriteOptions(),key);
		it->Next();
		i++;
	}
	delete it;
	return i;

}

Conversation* Database::getConversation(User* u1, User* u2){
	string key1 = u1->getUsername()+u2->getUsername();
	string value1 = this->get(this->conversationCF,key1);
	if (value1 != ""){
		Json::Reader r = Json::Reader();
		Json::Value val = Json::Value();
		r.parse(value1,val,false);
		return new Conversation(val);
	}
	else{
		string key2 = u2->getUsername()+u1->getUsername();
		string value2 = this->get(this->conversationCF,key2);
		if (value2 != "" ){
			Json::Reader r = Json::Reader();
			Json::Value val = Json::Value();
			r.parse(value1,val,false);
			return new Conversation(val);
		}
		else return NULL;
	}
}

bool Database::saveConversation(Conversation* conv){
	string json = conv->toJsonString();

	string key1 = conv->getFirstUser()->getUsername() + conv->getSecondUser()->getUsername();
	string value1 = this->get(key1);
	if (value1 != ""){
		return this->put(this->conversationCF,key1,json);
	}
	else{
		string key2 = conv->getSecondUser()->getUsername() + conv->getFirstUser()->getUsername();
		string value2 = this->get(key2);
		if (value2 != ""){
			return this->put(this->conversationCF,key2,json);
		}
	}
	return this->put(this->conversationCF,key1,json);
}
