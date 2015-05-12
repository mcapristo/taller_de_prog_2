/*
 * Server.h
 *
 *  Created on: 20/4/2015
 *      Author: mateo
 */

#ifndef SERVER_H_
#define SERVER_H_

#include <iostream>
#include "mongoose.h"
#include "json/json.h"
#include "Loggero.h"
#include "ServiceLayer.h"
#include "Proceso.h"

using namespace std;

class Server: public Proceso {
public:
	Server();
	virtual ~Server();
	void run();
	int ev_handler(mg_connection* conn, enum mg_event ev);

private:
	static int eventHandlerCaller(struct mg_connection *conn, enum mg_event ev);

	int handleLogin(mg_connection* conn);
	int handleLogout(mg_connection* conn);
	int handleValidateToken(mg_connection* conn);
	int handleCreateUser(mg_connection* conn);
	int handleUpdateUser(mg_connection* conn);
	int handleSendMessage(mg_connection* conn);
	int handleGetUsers(mg_connection* conn);
	int handleGetConversations(mg_connection* conn);
	int handleGetUser(mg_connection* conn);
	int handleGetMessagesWithUser(mg_connection* conn);

	string readRequestData(mg_connection* conn);
	string readRequestHeader(mg_connection* conn, string header);

	struct mg_server* sv;
	ServiceLayer* sl;

	Loggero* logger;
};

#endif /* SERVER_H_ */
