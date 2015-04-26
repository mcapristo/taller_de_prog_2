/*
 * Server.cpp
 *
 *  Created on: 20/4/2015
 *      Author: mateo
 */

#include "Server.h"

Server::Server() {
	this->sl = new ServiceLayer();
	this->sv = mg_create_server(this, Server::eventHandlerCaller);
	mg_set_option(this->sv, "listening_port", "8000");
	this->logger = Loggero::getInstnce();
}

void Server::run(){
	printf("Starting on port %s\n", mg_get_option(this->sv, "listening_port"));
	for (;;) {
		mg_poll_server(this->sv, 1000);
	}
}

Server::~Server() {
}

int Server::eventHandlerCaller(mg_connection* conn, enum mg_event ev){
	Server* s = (Server*) conn->server_param;
	return s->ev_handler(conn,ev);
}

int Server::ev_handler(mg_connection* conn, enum mg_event ev){
	switch (ev) {
		case MG_AUTH: return MG_TRUE;
		case MG_REQUEST:
			if (strcmp("/api/login", conn->uri)==0){
				this->handleLogin(conn);
				return MG_TRUE;
			}
			if (strcmp("/api/token", conn->uri)==0){
				this->handleValidateToken(conn);
				return MG_TRUE;
			}
			if (strcmp("/api/user", conn->uri) == 0){
				if (strcmp(conn->request_method,"GET") == 0){
					if (conn->query_string){
						this->handleGetUser(conn);
						return MG_TRUE;
					}
					else{
						this->handleGetUsers(conn);
						return MG_TRUE;
					}
				}
				else if (strcmp(conn->request_method,"POST") == 0){
					this->handleCreateUser(conn);
					return MG_TRUE;
				}
			}
			else if (strcmp("/api/conversation", conn->uri)==0 && strcmp(conn->request_method,"GET") == 0){
				this->handleGetConversations(conn);
				return MG_TRUE;
			}
			else if((strcmp("/api/message", conn->uri)==0)){
				if (strcmp(conn->request_method,"GET") == 0 && conn->query_string){
					this->handleGetMessagesWithUser(conn);
					return MG_TRUE;
				}
				else if (strcmp(conn->request_method,"POST") == 0){
					this->handleSendMessage(conn);
					return MG_TRUE;
				}
			}
			return MG_MORE;
		default:
			return MG_FALSE;
	}
}

string Server::readRequestHeader(mg_connection* conn, string header){
	const char* headerPointer = mg_get_header(conn, header.c_str());
	string h = "";

	if (headerPointer){
		string h1(headerPointer);
		h = h1;
	}

	return h;
}

int Server::handleLogin(mg_connection* conn){
	// cout<<"login"<<endl;
	this->logger->log(1, "Login");

	string u = this->readRequestHeader(conn, "username");
	string p = this->readRequestHeader(conn, "password");
	string res = sl->login(u,p);
	mg_printf_data(conn,res.c_str());

	return 0;
}

int Server::handleValidateToken(mg_connection* conn){
	this->logger->log(Constants::INFO, "ValidateLogin");

	string u = this->readRequestHeader(conn, "username");
	string t = this->readRequestHeader(conn, "token");
	string res = sl->validateToken(u,t);
	mg_printf_data(conn, res.c_str());
	return 0;
}

string createString(const char* c, size_t len){
	if (c == NULL) return "";
	string res = "";
	for (size_t i = 0; i<len ; i++){
		res = res + c[i];
	}
	return res;
}

string Server::readRequestData(mg_connection* conn){
	const char* data = conn->content;
	size_t len = conn->content_len;
	string d = createString(data,len);

	return d;
}

int Server::handleCreateUser(mg_connection* conn){
	// cout<<"create user"<<endl;
	this->logger->log(1, "Create User");

	string d = this->readRequestData(conn);
	string res = sl->createUser(d);
	mg_printf_data(conn, res.c_str());

	return 0;
}

int Server::handleSendMessage(mg_connection* conn){
	// cout<<"sendMessage"<<endl;
	this->logger->log(1, "Send Message");

	string data = this->readRequestData(conn);
	string username = this->readRequestHeader(conn, "username");
	string token = this->readRequestHeader(conn, "token");
	string res = sl->sendMessage(username, token, data);
	mg_printf_data(conn, res.c_str());

	return 0;
}

int Server::handleGetUsers(mg_connection* conn){
	// cout<<"get users"<<endl;
	this->logger->log(1, "Get Users");

	string username = this->readRequestHeader(conn, "username");
	string token = this->readRequestHeader(conn, "token");
	string res = sl->getUsersProfile(username, token);
	mg_printf_data(conn,res.c_str());

	return 0;
}

int Server::handleGetConversations(mg_connection* conn){
	// cout<<"getConversations"<<endl;
	this->logger->log(1, "Get Conversations");

	string username = this->readRequestHeader(conn, "username");
	string token = this->readRequestHeader(conn, "token");
	string res = sl->getConversations(username,token);
	mg_printf_data(conn,res.c_str());

	return 0;
}

int Server::handleGetUser(mg_connection* conn){
	this->logger->log(1, "Get User");

	const char* queryPointer = conn->query_string;
	string q = "";
	if (queryPointer){
		string h1(queryPointer);
		q = h1;
	}
	char buffer[50];
	sscanf( q.c_str(), "username=%s", buffer);
	string userToVisit = string(buffer);
	string username = this->readRequestHeader(conn, "username");
	string token = this->readRequestHeader(conn, "token");
	string res = this->sl->getUserProfile(username,token,userToVisit);
	mg_printf_data(conn, res.c_str());

	return 0;
}

int Server::handleGetMessagesWithUser(mg_connection* conn){
	this->logger->log(1,"Get Messages With User");

	const char* queryPointer = conn->query_string;
	string q = "";
	if (queryPointer){
		string h1(queryPointer);
		q = h1;
	}
	char buffer[50];
	sscanf( q.c_str(), "username=%s", buffer);
	string user2 = string(buffer);
	string username = this->readRequestHeader(conn, "username");
	string token = this->readRequestHeader(conn, "token");
	string res = this->sl->getMessages(username,token,user2);
	mg_printf_data(conn, res.c_str());

	return 0;
}
