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

	// Create and configure the server
	mg_set_option(this->sv, "listening_port", "8000");

	// Serve request. Hit Ctrl-C to terminate the program
	printf("Starting on port %s\n", mg_get_option(this->sv, "listening_port"));
	for (;;) {
		mg_poll_server(this->sv, 1000);
	}
}

Server::~Server() {
}

int Server::eventHandlerCaller(mg_connection* conn, enum mg_event ev){
	Server* s = (Server*) conn->server_param;
//	cout<<conn->uri<<endl;
	cout<<"bien ruteada"<<endl;
	s->ev_handler(conn,ev);
	return 1;
}

int Server::ev_handler(mg_connection* conn, enum mg_event ev){

	switch(ev){
	case MG_AUTH: return MG_TRUE;
	case MG_REQUEST:
		if (!strcmp(conn->uri, "/api/login")) {
			return this->handleLogin(conn);
		}
		return MG_TRUE;
	default: return MG_FALSE;
	}
}

int Server::handleLogin(mg_connection* conn){
	cout<<"login"<<endl;
	const char* username = mg_get_header(conn,"username");
	const char* password = mg_get_header(conn,"password");
	cout<<username<<endl;
	cout<<password<<endl;
	return 1;
}
