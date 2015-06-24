/*
 * Database.cpp
 *
 *  Created on: 8/4/2015
 *      Author: mateo
 */

#include "Database.h"

/**
 * Creates the Database, empty if it does not exist
 * or initiates an existing one
 */
Database::Database() {
	Options options;
	options.create_if_missing = true;
	Status s = DB::Open(options, "database", &this->db);
	if (s.ok()){
		s = db->CreateColumnFamily(ColumnFamilyOptions(), "UserCF", &this->userCF);
		assert(s.ok());

		s = db->CreateColumnFamily(ColumnFamilyOptions(), "ConversationCF", &this->conversationCF);
		assert(s.ok());

		s = db->CreateColumnFamily(ColumnFamilyOptions(), "MessageCF", &this->messageCF);
		assert(s.ok());
		delete this->userCF;
		delete this->conversationCF;
		delete this->messageCF;
		delete this->db;
	}
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

Database::~Database() {
	delete this->defaultCF;
	delete this->userCF;
	delete this->conversationCF;
	delete this->messageCF;
	delete this->db;
}
/**
 *
 * @param key the key of the key-value pair
 * @return the value as string
 */
string Database::get(string key) {
	return this->get(this->defaultCF,key);
}

/**
 *
 * @param key from key-value to persist in the database
 * @param value from key-value to persist in the database
 * @return true if OK, false if not OK
 */
bool Database::put(string key, string value) {
	return this->put(this->defaultCF,key,value);
}

/**
 *
 * @param cfHandle the ColumnFamilyHandler
 * @param key
 * @return value in database
 */
string Database::get(ColumnFamilyHandle* cfHandle, string key) {
	string value;
	Status res = this->db->Get(ReadOptions(),cfHandle,key,&value);
//	cout<< "GET from "+ cfHandle->GetName()+" :clave: '" + key + "', valor: '" + value +"'"<< endl;
	return value;
}

/**
 *
 * @param cfHandle the ColumnFamilyHandler of key-value
 * @param key the key
 * @param value to persist
 * @return true if OK, false if not OK
 */
bool Database::put(ColumnFamilyHandle* cfHandle,string key, string value) {
//	cout<< "SET in "+ cfHandle->GetName() +": clave: '" + key + "', valor: '" + value +"'" << endl;
	WriteOptions wo = WriteOptions();
	Status res = db->Put(wo,cfHandle, key, value);
	return res.ok();
}

/**
 *
 * @param str a json string
 * @return the json string parsed as Json::Value
 */
Json::Value Database::getJsonValueFromString(string str) {
	Json::Reader r = Json::Reader();
	Json::Value val = Json::Value();
	r.parse(str,val,false);
	return val;
}

/**
 *
 * @param value a Json::Value to convert to string
 * @return the json as a string
 */
string Database::getJsonStringFromValue(Json::Value value){
	Json::StreamWriterBuilder builder;
	builder.settings_["identation"] = "\t";
	return Json::writeString(builder,value);
}

/**
 *
 * @param key the username
 * @return a pointer to User in database
 */
User* Database::getUser(string key) {
	string json = this->get(this->userCF,key);
	if (json == "") return NULL;
	Json::Value val = this->getJsonValueFromString(json);
	UserFactory uf = UserFactory();
	User* u = uf.createUserFromJsonValue(val);
	return u;
}

/**
 *
 * @param user a pointer to User to persist in the database
 * @return true if OK, false if not OK
 */
bool Database::saveUser(User* user) {
	string username = user->getUsername();
	string json = user->toJsonString();
	return this->put(this->userCF,username,json);
}

/**
 *
 * @param id of the message
 * @return a pointer to the message in database
 */
Message* Database::getMessage(string id){
	string json = this->get(this->messageCF,id);
	Json::Value val = this->getJsonValueFromString(json);
	return new Message(val);
}

/**
 *
 * @param m a pointer to the Message
 * @param key the id of the message
 * @return true if OK, false if not OK
 */
bool Database::saveMessageWithKey(Message* m, string key){

	string conversationJson = this->get(this->conversationCF,key);
	Conversation* conv;
	if (conversationJson == ""){
		conv = new Conversation(m->getEmisor(),m->getReceptor());
	}
	else {
		Json::Value val = this->getJsonValueFromString(conversationJson);
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
/**
 *
 * @param m a pointer to the message to persist in the database
 * @return true if OK, false if not OK
 */
bool Database::saveMessage(Message* m) {
	Conversation* conv = this->getConversation(m->getEmisor(),m->getReceptor());

	if (conv != NULL){
		string id = conv->getId();
		delete conv;
		return this->saveMessageWithKey(m,id);
	}
	else{
		string key2 = m->getEmisor()->getUsername() + m->getReceptor()->getUsername();
		return this->saveMessageWithKey(m,key2);
	}

}

/**
 *
 * @return how many values were deleted
 */
int Database::deleteDatabaseValues(){
	std::vector<ColumnFamilyHandle*> column_families;
	column_families.push_back(this->defaultCF);
	column_families.push_back(this->userCF);
	column_families.push_back(this->messageCF);
	column_families.push_back(this->conversationCF);
	int i = 0;
	for (size_t j = 0; j< column_families.size();j++){
		Iterator* it = this->db->NewIterator(ReadOptions(),column_families[j]);
		it->SeekToFirst();
		while (it->Valid()){
			Slice key = it->key();
			this->db->Delete(WriteOptions(),column_families[j],key);
			it->Next();
			i++;
		}
		delete it;
	}
	return i;
}

/**
 *
 * @param u1 One of the users in the conversation
 * @param u2 The other user in the conversation
 * @return a pointer to the Conversation in database
 */
Conversation* Database::getConversation(User* u1, User* u2){
	string key1 = u1->getUsername()+u2->getUsername();
	string value1 = this->get(this->conversationCF,key1);
	if (value1 != ""){
		Json::Value val = this->getJsonValueFromString(value1);
		return new Conversation(val);
	}
	else{
		string key2 = u2->getUsername()+u1->getUsername();
		string value2 = this->get(this->conversationCF,key2);
		if (value2 != "" ){
			Json::Value val = this->getJsonValueFromString(value2);
			return new Conversation(val);
		}
		else return NULL;
	}
}

/**
 *
 * @param conv a pointer to the conversation to save in database
 * @return true if OK, false if not OK
 */
bool Database::saveConversation(Conversation* conv){
	string key1 = conv->getFirstUser()->getUsername() + conv->getSecondUser()->getUsername();
	string value1 = this->get(key1);
	if (value1 != ""){
		conv->setId(key1);
		string json = conv->toJsonString();
		return this->put(this->conversationCF,key1,json);
	}
	else{
		string key2 = conv->getSecondUser()->getUsername() + conv->getFirstUser()->getUsername();
		string value2 = this->get(key2);
		if (value2 != ""){
			conv->setId(key2);
			string json = conv->toJsonString();
			return this->put(this->conversationCF,key2,json);
		}
	}
	conv->setId(key1);
	string json = conv->toJsonString();
	return this->put(this->conversationCF,key1,json);
}

/**
 *
 * @return a vector of pointers to the users in the database
 */
vector<User*> Database::getUsers(){
	ColumnFamilyHandle* h = this->userCF;
	Iterator* it = this->db->NewIterator(ReadOptions(),h);
	vector<User*> users = vector<User*>();
	UserFactory uf = UserFactory();
	it->SeekToFirst();
	while (it->Valid()){
		Slice userKey = it->key();
		string value = this->get(h,userKey.ToString());
		User* u = uf.createUserFromJsonString(value);
		users.push_back(u);
		it->Next();
	}
	delete it;
	return users;
}
/**
 *
 * @return a json value of all the users in the database
 */
Json::Value Database::getUsersJsonValue(){
	ColumnFamilyHandle* h = this->userCF;
	Iterator* it = this->db->NewIterator(ReadOptions(),h);
	Json::Value jsonValue = Json::Value();
	Json::Value jsonVec = Json::Value();
	it->SeekToFirst();
	while (it->Valid()){
		Slice userKey = it->key();
		string value = this->get(h,userKey.ToString());
		Json::Value auxiliarValue = this->getJsonValueFromString(value);
		jsonVec.append(auxiliarValue);
		it->Next();
	}
	jsonValue["users"] = jsonVec;
	delete it;
	return jsonValue;

}

/**
 *
 * @return a json string of all the users in the database
 */
string Database::getUsersJsonString(){
	Json::Value jsonValue = this->getUsersJsonValue();
	Json::StreamWriterBuilder builder;
	builder.settings_["identation"] = "\t";
	return Json::writeString(builder,jsonValue);
}

/**
 *
 * @param conv the conversation that contains all the messages that you want
 * @return a Json::Value of all the messages in the conversation
 */
Json::Value Database::getMessagesJsonValue(Conversation* conv){
	int tot_msg = conv->getTotalMessages();
	Json::Value arrayValue = Json::Value();
	string conversationID = conv->getId();
	ColumnFamilyHandle* cf = this->messageCF;

	for (int i = 0; i< tot_msg; i++){
		stringstream ss;
		ss << i;
		string str = ss.str();
		string messageID = conversationID + str;
		string messageJson = this->get(cf,messageID);
		Json::Value messageValue = this->getJsonValueFromString(messageJson);
		arrayValue.append(messageValue);
	}
	return arrayValue;
}

/**
 *
 * @param conv the conversation that contains all the messages that you want to retreive from the database
 * @return a json string that contains all the messages
 */
string Database::getMessagesJsonString(Conversation* conv){
	Json::Value jsonValue = this->getMessagesJsonValue(conv);
	Json::StreamWriterBuilder builder;
	builder.settings_["identation"] = "\t";
	return Json::writeString(builder,jsonValue);
}

/**
 *
 * @param user a pointer to a user
 * @return all the conversations that this user has
 */
vector<Conversation*> Database::getConversations(User* user){
	vector<User*> users = this->getUsers();
	vector<Conversation*> conversations = vector<Conversation*>();
	for(size_t i = 0; i < users.size(); i++){
		User* u = users[i];
		Conversation* c = this->getConversation(user, u);
		if (c != NULL){
			conversations.push_back(c);
		}
		delete u;
	}
	return conversations;
}

