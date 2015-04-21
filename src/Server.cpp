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
	cout<<"bien ruteada"<<endl;
	return s->ev_handler(conn,ev);
}


int Server::ev_handler(mg_connection* conn, enum mg_event ev){
	switch (ev) {
		case MG_AUTH: return MG_TRUE;
		case MG_REQUEST:
			if (strcmp("/api/login", conn->uri)==0){
				mg_printf_data(conn,conn->request_method);
				this->handleLogin(conn);
				return MG_TRUE;
			}
			if (strcmp("/api/user", conn->uri) == 0 && strcmp(conn->request_method,"POST") == 0){
				this->handleCreateUser(conn);
				return MG_TRUE;
			}
			return MG_MORE;
		default: return MG_FALSE;
	}
}

int Server::handleLogin(mg_connection* conn){
	cout<<"login"<<endl;
	const char* username = mg_get_header(conn,"username");
	const char* password = mg_get_header(conn,"password");
	string u,p;
	if (username) string u(username);
	else string u("");
	if (password) string p(password);
	else string p("");
	string res = sl->login(u,p);
	mg_printf_data(conn,res.c_str());
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

int Server::handleCreateUser(mg_connection* conn){
	cout<<"create user"<<endl;
	const char* data = conn->content;
	size_t len = conn->content_len;
	string d = createString(data,len);
	string res = sl->createUser(d);
	mg_printf_data(conn, res.c_str());
	return 0;
}


