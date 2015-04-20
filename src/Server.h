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
#include "ServiceLayer.h"

using namespace std;

class Server {
public:
	Server();
	virtual ~Server();

private:
	static int eventHandlerCaller(struct mg_connection *conn, enum mg_event ev);
	int ev_handler(mg_connection* conn, enum mg_event ev);

	int handleLogin(mg_connection* conn);


	struct mg_server* sv;
	ServiceLayer* sl;
};

#endif /* SERVER_H_ */
